#include <iostream>
#include <iomanip>

using namespace std;

int64_t bitcount(int64_t n);
int64_t numbytes(int64_t bitCount);
int64_t padcalculator(int64_t n, int64_t bitCount);
int64_t pad(int64_t num, int64_t n, int64_t bitCount, int64_t padLength);
void hexoutput(int64_t result);

int main(){
    int64_t n;
    
    //loop to get data and do all my shiz with
    while(cin >> n){
        int64_t count = bitcount(n);        
        int64_t bytes = numbytes(count);
        int64_t padLength = padcalculator(bytes, count);
        int64_t result = pad(n, bytes, count, padLength);
        
        //output
        cout << n << ":";
        int64_t shift;
        for(int64_t i = (count + padLength); i > 0; i -=8){
            shift = result >> (i - 4);
            hexoutput(shift);
        }
        cout << '\n';
    }
    
    //input validation
    if(!cin.eof())
        cerr << "Read failed, but not at eof. Integers only please.\n";
    
    
    return 0;
}

//a function that returns the number of bits used to represent n
int64_t bitcount(int64_t n){
    int64_t absNum = abs(n);
    int64_t count = 0;
    while(absNum > 0){
        absNum /= 2;
        count++;
    }
    count++; //add one bit for signed bit
    return count;
}

//a function that solves for n in the equation bitCount = 8n+4
//used in padCalculator
int64_t numbytes(int64_t bitCount){
    int64_t n;
    if(bitCount <= 4 && bitCount >0)
        n = 0;
    else if(bitCount <= 12 && bitCount > 4)
        n = 1;
    else if(bitCount <= 20 && bitCount > 12)
        n = 2;
    else if(bitCount <= 28 && bitCount > 20)
        n = 3;
    else if(bitCount <= 36 && bitCount > 28)
        n = 4;
    
    return n;
}

int64_t padcalculator(int64_t n, int64_t bitCount){
    int64_t padTarget = (8 * n) + 4;
    int64_t padLength = padTarget - bitCount;
    
    return padLength;
}

int64_t pad(int64_t num, int64_t n, int64_t bitCount, int64_t padLength){
    int64_t result;
    if(num > 0){
        //int64_t is positive
        n <<= bitCount; //shifts n left by bit field, puts n at top of integer
        n <<= padLength; //shifts n left by padLength, puts padding between n and top of integer
        
        //n is now a mask
        result = n | num;
    }
    else if(num < 0){
        //int64_t is negative
        int64_t absNum = abs(num); //force number positive because of weird compiler two's complement interpretation
        
        //two's complement
        absNum = ~absNum;
        absNum++;
        
        //maintain 1s except in length nibble
        int64_t mask = 0b1111;
        mask <<= bitCount;
        mask <<= padLength;
        mask = ~mask;
        absNum = absNum & mask;
        //shift n, see positive numbers
        n <<= bitCount;
        n <<= padLength;
        
        result = n | absNum;
    }
    else{
        //int64_t is zero
        result = num;
    }
    
    return result;
}

void hexoutput(int64_t result){
    cout << " " << hex << setw(2) << setfill('0') << (result & 0xff) << dec;
}








