
#include "stats.h"
#define DEBUG 0

stats::stats(PNG & im){
    
    for(unsigned int x = 0; x < im.width(); x++){
        sumRed.push_back( vector<long>() );
        sumGreen.push_back( vector<long>() );
        sumBlue.push_back( vector<long>() );
        sumsqRed.push_back( vector<long>() );
        sumsqGreen.push_back( vector<long>() );
        sumsqBlue.push_back( vector<long>() );
        for(unsigned int y = 0; y < im.height(); y++){
            #if DEBUG
                cout << "constructor: " << x << " " << y << endl;
            #endif

            sumRed[x].push_back (y == 0 ? 0 : sumRed[x][y-1]);
            sumRed[x][y] += x == 0 ? 0 : (sumRed[x-1][y] - (y == 0 ? 0 :sumRed[x-1][y-1]));
            sumRed[x][y] += im.getPixel(x,y)->r;

            sumGreen[x].push_back (y == 0 ? 0 : sumGreen[x][y-1]);
            sumGreen[x][y] += x == 0 ? 0 : (sumGreen[x-1][y] - (y == 0 ? 0 :sumGreen[x-1][y-1]));
            sumGreen[x][y] += im.getPixel(x,y)->g;

            sumBlue[x].push_back (y == 0 ? 0 : sumBlue[x][y-1]);
            sumBlue[x][y] += x == 0 ? 0 : (sumBlue[x-1][y] - (y == 0 ? 0 :sumBlue[x-1][y-1]));
            sumBlue[x][y] += im.getPixel(x,y)->b;

            sumsqRed[x].push_back (y == 0 ? 0 : sumsqRed[x][y-1]);
            sumsqRed[x][y] += x == 0 ? 0 : (sumsqRed[x-1][y] - (y == 0 ? 0 :sumsqRed[x-1][y-1]));
            sumsqRed[x][y] += im.getPixel(x,y)->r * im.getPixel(x,y)->r;

            sumsqGreen[x].push_back (y == 0 ? 0 : sumsqGreen[x][y-1]);
            sumsqGreen[x][y] += x == 0 ? 0 : (sumsqGreen[x-1][y] - (y == 0 ? 0 :sumsqGreen[x-1][y-1]));
            sumsqGreen[x][y] += im.getPixel(x,y)->g * im.getPixel(x,y)->g;

            sumsqBlue[x].push_back (y == 0 ? 0 : sumsqBlue[x][y-1]);
            sumsqBlue[x][y] += x == 0 ? 0 : (sumsqBlue[x-1][y] - (y == 0 ? 0 :sumsqBlue[x-1][y-1]));
            sumsqBlue[x][y] += im.getPixel(x,y)->b * im.getPixel(x,y)->b;
        }
    }
}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

    switch(channel){
        //pair<int, int> pair(x,y); 
        case 'r':
            return (
                sumRed[lr.first][lr.second] - 
                (ul.first == 0 ? 0 : sumRed[ul.first-1][lr.second]) - 
                (ul.second == 0 ? 0 : sumRed[lr.first][ul.second-1]) +
                (ul.first == 0 || ul.second == 0 ? 0 : sumRed[ul.first-1][ul.second-1])
            );
            break;
        case 'g':
            return (
                sumGreen[lr.first][lr.second] - 
                (ul.first == 0 ? 0 : sumGreen[ul.first-1][lr.second]) - 
                (ul.second == 0 ? 0 : sumGreen[lr.first][ul.second-1]) +
                (ul.first == 0 || ul.second == 0 ? 0 : sumGreen[ul.first-1][ul.second-1])
            );
        break;
        case 'b':
            return (
                sumBlue[lr.first][lr.second] - 
                (ul.first == 0 ? 0 : sumBlue[ul.first-1][lr.second]) - 
                (ul.second == 0 ? 0 : sumBlue[lr.first][ul.second-1]) +
                (ul.first == 0 || ul.second == 0 ? 0 : sumBlue[ul.first-1][ul.second-1])
            );
        break;
        default:
            cout << "GETSUM BROKEN" <<endl;
            return 0;
        break;
    }

}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

    switch(channel){
        case 'r':
            return (
                sumsqRed[lr.first][lr.second] - 
                (ul.first == 0 ? 0 : sumsqRed[ul.first-1][lr.second]) - 
                (ul.second == 0 ? 0 : sumsqRed[lr.first][ul.second-1]) +
                (ul.first == 0 || ul.second == 0 ? 0 : sumsqRed[ul.first-1][ul.second-1])
            );
            break;
        case 'g':
            return (
                sumsqGreen[lr.first][lr.second] - 
                (ul.first == 0 ? 0 : sumsqGreen[ul.first-1][lr.second]) - 
                (ul.second == 0 ? 0 : sumsqGreen[lr.first][ul.second-1]) +
                (ul.first == 0 || ul.second == 0 ? 0 : sumsqGreen[ul.first-1][ul.second-1])
            );
        break;
        case 'b':
            return (
                sumsqBlue[lr.first][lr.second] - 
                (ul.first == 0 ? 0 : sumsqBlue[ul.first-1][lr.second]) - 
                (ul.second == 0 ? 0 : sumsqBlue[lr.first][ul.second-1]) +
                (ul.first == 0 || ul.second == 0 ? 0 : sumsqBlue[ul.first-1][ul.second-1])
            );
        break;
        default:
            cout << "GETSUMSQ BROKEN" <<endl;
            return 0;
        break;
    }
    
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
    
    #if debug
    cout<<"upper left x: "<<ul.first; 
    cout<<"upper left y: "<<ul.second; 
    cout<<"lower right x: "<<lr.first; 
    cout<<"lower right y: "<<lr.second<<endl;
    #endif

    return (lr.first+1-ul.first)*(lr.second+1-ul.second);

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

    #if DEBUG
        cout << "getScore: " << endl << (getSumSq('r',ul,lr) - ((getSum('r',ul,lr) * getSum('r',ul,lr)) / rectArea(ul, lr))) +
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

    return RGBAPixel(
        getSum('r',ul,lr)/rectArea(ul,lr),
        getSum('g',ul,lr)/rectArea(ul,lr),
        getSum('b',ul,lr)/rectArea(ul,lr)
    );
}
