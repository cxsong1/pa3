
#include "stats.h"
#define DEBUG 1

stats::stats(PNG & im){
    
    for(unsigned int x = 0; x < im.width()-1; x++){
        sumRed.push_back( vector<long>() );
        sumGreen.push_back( vector<long>() );
        sumBlue.push_back( vector<long>() );
        sumsqRed.push_back( vector<long>() );
        sumsqGreen.push_back( vector<long>() );
        sumsqBlue.push_back( vector<long>() );
        for(unsigned int y = 0; y < im.height()-1; y++){
            #if DEBUG
                cout << "constructor: " << x << " " << y << endl;
            #endif
            pair<int,int> lr(x,y);

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

            cout << "pixel value: " << this->img.getPixel(x,y)->r << " " <<this->img.getPixel(x,y)->g << " " << this->img.getPixel(x,y)->b<< endl;
        }
    }
}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

    switch(channel){
        case 'r':
            return sumRed[lr.first][lr.second]-sumRed[lr.first][ul.second]-sumRed[ul.first][lr.second]+sumRed[ul.first][ul.second];
        break;
        case 'g':
            return sumGreen[lr.first][lr.second] -sumGreen[lr.first][ul.second] - sumGreen[ul.first][lr.second] + sumGreen[ul.first][ul.second]; 
        break;
        case 'b':
            return sumBlue[lr.first][lr.second]-sumBlue[lr.first][ul.second] - sumBlue[ul.first][lr.second] + sumBlue[ul.first][ul.second]; 
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
            return sumsqRed[lr.first][lr.second]-sumsqRed[lr.first][ul.second]-sumsqRed[ul.first][lr.second]+sumsqRed[ul.first][ul.second];
        break;
        case 'g':
            return sumsqGreen[lr.first][lr.second] -sumsqGreen[lr.first][ul.second] - sumsqGreen[ul.first][lr.second] + sumsqGreen[ul.first][ul.second]; 
        break;
        case 'b':
            return sumsqBlue[lr.first][lr.second]-sumsqBlue[lr.first][ul.second] - sumsqBlue[ul.first][lr.second] + sumsqBlue[ul.first][ul.second]; 
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
