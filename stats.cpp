
#include "stats.h"
#define DEBUG 1

stats::stats(PNG & im){
    this->im = im;
    pair<int,int> origin(0,0);
    for(unsigned int x = 0; x < im.width()-1; x++){
        sumRed.push_back( vector<long>() );
        sumGreen.push_back( vector<long>() );
        sumBlue.push_back( vector<long>() );
        sumsqRed.push_back( vector<long>() );
        sumsqGreen.push_back( vector<long>() );
        sumsqBlue.push_back( vector<long>() );
        for(unsigned int y = 0; y < im.height()-1; y++){

            pair<int,int> lr(x,y);
            sumRed[x].push_back( getSum('r', origin, lr) );
            sumGreen[x].push_back( getSum('g', origin, lr) );
            sumBlue[x].push_back( getSum('b', origin, lr) );
            sumsqRed[x].push_back( getSumSq('r', origin, lr) );
            sumsqGreen[x].push_back( getSumSq('g', origin, lr) );
            sumsqBlue[x].push_back( getSumSq('b', origin, lr) ); 
        }
    }
}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

    int rollingSum = 0;
    for(int x = ul.first; x < lr.first; x++){
        for(int y = ul.second; y < lr.second; y++){
            switch(channel){
                case 'r':
                    rollingSum += (int)im.getPixel(x,y)->r;
                break;
                case 'g':
                    rollingSum += (int)im.getPixel(x,y)->g;
                break;
                case 'b':
                    rollingSum += (int)im.getPixel(x,y)->b;
                break;
            }
        }
    }
    #if DEBUG
        cout << "getSum: " << rollingSum << endl;
    #endif
    return rollingSum;

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

    long rollingSum = 0;
        for(int x = ul.first; x < lr.first; x++){
            for(int y = ul.second; y < lr.second; y++){
                switch(channel){
                    case 'r':
                        rollingSum += ((int)im.getPixel(x,y)->r * (int)im.getPixel(x,y)->r);
                    break;
                    case 'g':
                        rollingSum += ((int)im.getPixel(x,y)->g * (int)im.getPixel(x,y)->g);
                    break;
                    case 'b':
                        rollingSum += ((int)im.getPixel(x,y)->b * (int)im.getPixel(x,y)->b);
                    break;
                }
            }
        }
    
    #if DEBUG
        cout << "getSumSq: " << rollingSum << endl;
    #endif
    return rollingSum; 
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

    return (ul.first-lr.first)*(ul.second-lr.second);

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getSScore(pair<int,int> ul, pair<int,int> lr){

    #if DEBUG
        cout << "getScore: " << (getSumSq('r',ul,lr) - ((getSum('r',ul,lr) * getSum('r',ul,lr)) / rectArea(ul, lr))) +
        (getSumSq('b',ul,lr) - ((getSum('b',ul,lr) * getSum('b',ul,lr)) / rectArea(ul, lr))) +
        (getSumSq('g',ul,lr) - ((getSum('g',ul,lr) * getSum('g',ul,lr)) / rectArea(ul, lr))) << endl;
    #endif
    return (
        (getSumSq('r',ul,lr) - ((getSum('r',ul,lr) * getSum('r',ul,lr)) / rectArea(ul, lr))) +
        (getSumSq('b',ul,lr) - ((getSum('b',ul,lr) * getSum('b',ul,lr)) / rectArea(ul, lr))) +
        (getSumSq('g',ul,lr) - ((getSum('g',ul,lr) * getSum('g',ul,lr)) / rectArea(ul, lr)))
    );

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
    return RGBAPixel(
        getSum('r',ul,lr)/rectArea(ul,lr),
        getSum('g',ul,lr)/rectArea(ul,lr),
        getSum('b',ul,lr)/rectArea(ul,lr)
    );
}
