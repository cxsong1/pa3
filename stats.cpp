
#include "stats.h"

stats::stats(PNG & im){

    this->im = im;
    pair<int,int> origin(0,0);
    for(int x = 0; x < im.width()-1; x++){
        for(int y = 0; y < im.height()-1; y++){
            pair<int,int> lr(x,y);
            sumRed[x][y] = getSum('r', origin, lr);
            sumGreen[x][y] = getSum('g', origin, lr);
            sumBlue[x][y] = getSum('b', origin, lr);
            sumsqRed[x][y] = getSumSq('r', origin, lr);
            sumsqGreen[x][y] = getSumSq('g', origin, lr);
            sumsqBlue[x][y] = getSumSq('b', origin, lr); 
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
    return rollingSum; 
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
    return (ul.first-lr.first)*(ul.second-lr.second);

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!



}
		
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
    return RGBAPixel(
        getSum('r',ul,lr)/rectArea(ul,lr),
        getSum('g',ul,lr)/rectArea(ul,lr),
        getSum('b',ul,lr)/rectArea(ul,lr)
    );
}
