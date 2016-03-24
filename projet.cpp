#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectFaceAndEye( Mat frame );

/** Global variables */
String discEtoile_cascade_name = "haarcascades/cascadeDiscEtoile.xml";

CascadeClassifier disEtoile_cascade;
String window_name = "PIMA - author: TAN Tam Tai";
int total = 0;
int detect = 0;

/** @function detecstAndDisplay */
void detectFaceAndEye( Mat frame, string filename )
{
    std::vector<Rect> disEtoile;
    Mat frame_gray;
    
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //localiser visage
    disEtoile_cascade.detectMultiScale( frame_gray, disEtoile, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(50, 50) );

    for ( size_t i = 0; i < disEtoile.size(); i++ )
    {
        Point center( disEtoile[i].x + disEtoile[i].width/2, disEtoile[i].y + disEtoile[i].height/2 );
        ellipse( frame, center, Size( disEtoile[i].width/2, disEtoile[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 1, 1, 0 );
		
        //Mat faceROI = frame_gray( faces[i] );
        /*std::vector<Rect> eyes;
		//localiser des yeux
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 3, 0 |CASCADE_SCALE_IMAGE, Size(15, 15) );
        
        
        
        
		cout<<"nb eye detection dans image: "<< eyes.size() << endl;
		
		if(eyes.size() >= 1){
			detect++;
			size_t j =0;
			if(eyes.size() >= 2){
				size_t k=1;
				while ( k < eyes.size() )
				{
					if(eyes[k].width > eyes[k-1].width)
						j=k;
					k++;
				}
			}
			Point eye_centerLeft( faces[i].x + eyes[j].x + eyes[j].width/4, faces[i].y + eyes[j].y + eyes[j].height/2 );
			Point eye_centerRight( faces[i].x + eyes[j].x + eyes[j].width/4 + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
			int radius = cvRound( (eyes[j].width + eyes[j].height)/8 );
			circle( frame, eye_centerLeft, radius, Scalar( 255, 0, 0 ), 5, 5, 0 );
			circle( frame, eye_centerRight, radius, Scalar( 255, 0, 0 ), 5, 5, 0 );
					
        }*/
    }
    //Photos show
	string dirName = "result/";
    string imgPath(dirName + filename);
    imwrite( imgPath, frame );
	//imshow( window_name, frame );
	//cv::waitKey(0);
}


/** @function main */
int main( void )
{
    Mat frame;
	system("exec rm -rf result/*");
    //chargement les cascades
    if( !disEtoile_cascade.load( discEtoile_cascade_name ) ){
		printf("ERREUR de chargement Face Cascade\n"); 
		return -1; 
    };
	
    string dirName = "lib/DisEtoileTest/";
	DIR *dir;
    dir = opendir(dirName.c_str());
    string imgName;
    struct dirent *ent;
    //float_t percent;
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
			string filename(ent->d_name);
			if(filename.compare(".") !=0 && filename.compare("..")!=0){
				string imgPath(dirName + ent->d_name);
				cout<<"image path: "<< imgPath << endl;
				frame = imread(imgPath);
				if(!frame.data) { 
                    printf("ERREUR de chargement Image \n");
					return -1; 
				}
				
        //		total++;
				detectFaceAndEye(frame, filename);
                //percent = (float(detect)/float(total))*100;
                //cout<<"detected "<< detect<<"/"<<total<<" completed: "<<percent<<"%"<<endl;
			}
        }
        closedir (dir);
    }
    //else {
     //   cout<<"not present"<<endl;
   // }
	
    //cout<<"completed "<<percent<<"% de la base de données"<<endl;
    //return 0;
}


