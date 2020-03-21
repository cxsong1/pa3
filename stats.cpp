
#include "stats.h"

stats::stats(PNG & im){

    this->im = im;
    pair origin(0,0);
    for(int x = 0; x < im.width(); x++){
        for(int y = 0; y < im.height(); y++){
            pair lr(x,y);
            sumRed = getSum(r, origin, lr);
            sumGreen = getSum(g, origin, lr);
            sumBlue = getSum(b, origin, lr);
            sumsqRed = getSumSq(r, origin, lr);
            sumsqGreen = getSumSq(g, origin, lr);
            sumsqBlue = getSumSq(b, origin, lr); 
        }
    }
}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

    int rollingSum = 0;
    for(int x = ul.first; x < lr.first; x++){
        for(int y = ul.second; y < lr.sencond; y++){
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

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

    int rollingSum = 0;
        for(int x = ul.first; x < lr.first; x++){
            for(int y = ul.second; y < lr.sencond; y++){
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

}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!

}
