
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std ;
using namespace cv ;

Mat logFunc( Mat& ) ;
Mat inverseLogFunc( Mat& ) ;

int main( int argc , char** argv )
{
	Mat input = imread( "YUI01.jpg" , 1 ) ;
	Mat hsvImg ;

	if( !input.data )
	{
		cout << "input failed.\n" ;
	}

	cvtColor( input , hsvImg , CV_BGR2HSV ) ;
	vector< Mat > channels ;
	split( hsvImg , channels ) ;
	imshow( "hsv" , hsvImg ) ;

	imshow( "h" , channels[ 0 ] ) ;
	imshow( "s" , channels[ 1 ] ) ;
	imshow( "v" , channels[ 2 ] ) ;

	vector< Mat > logHSV , inverseLogHSV ;
	for( int i = 0 ; i < channels.size( ) ; i ++ )
	{
		logHSV.push_back( logFunc( channels[ i ] ) ) ;
		inverseLogHSV.push_back( inverseLogFunc( channels[ i ] ) ) ;
	}

	imshow( "log h" , logHSV[ 0 ] ) ;
	imshow( "log s" , logHSV[ 1 ] ) ;
	imshow( "log v" , logHSV[ 2 ] ) ;
	imshow( "inverse log h" , inverseLogHSV[ 0 ] ) ;
	imshow( "inverse log s" , inverseLogHSV[ 1 ] ) ;
	imshow( "inverse log v" , inverseLogHSV[ 2 ] ) ;
	

	waitKey( 0 ) ;

	return 0 ;
}

Mat logFunc( Mat& hsv )
{
	Mat log( hsv.size( ) , hsv.depth( ) ) ;
	for( int i = 0 ; i < hsv.rows ; i ++ )
	{
		for( int j = 0 ; j < hsv.cols ; j ++ )
		{
			log.at< uchar >( i , j ) = std :: log( hsv.at< uchar >( i , j ) + 1 ) * 32 ;
		}
	}
	return log ;
}

Mat inverseLogFunc( Mat& hsv )
{
	Mat inverse( hsv.size( ) , hsv.depth( ) ) ;
	for( int i = 0 ; i < hsv.rows ; i ++ )
	{
		for( int j = 0 ; j < hsv.cols ; j ++ )
		{
			inverse.at< uchar >( i , j ) = pow( 2 , ( hsv.at< uchar >( i , j ) / 32 ) ) - 1 ;
		}
	}
	return inverse ;
}