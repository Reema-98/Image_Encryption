
#include <bits/stdc++.h>
//#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<bits/stdc++.h>
#include <string>
using namespace std;
using namespace cv;


int rows;
int cols;
//string fileName, ext;
/*******************/
vector<int> rotate(vector<int> vec, int d)
{

    // Push first d elements from the beginning
    // to the end and remove those elements
    // from the beginning
    for (int i = 0; i < d; i++) {
        vec.push_back(vec[0]);
        vec.erase(vec.begin());
    }


    return vec;
}
/*******************/
vector <int> createPermutation(string key, int N){
    int cumSum =key[0];
    vector <int> A;
    int j =0;
    unordered_set <int> seen;
    int keyCum;
    for(int i =1;i<=N;++i) {
        if(i<key.length()){
            cumSum = (cumSum +key[i])%N;
        }
        else if(j<i){
            if(i==key.length()){

                keyCum = cumSum;
                cout<<"Key: "<<key<<endl;
                cout<<"Setting key cum sum: "<<keyCum<<"\n";
            }
            cumSum=(cumSum +A[j])%N;
            j++;
        }
        else{

            cumSum=(cumSum + A[0])%N;
            j=1;
        }
        A.push_back(cumSum);
    }



    int lind=0,rind = N-1, flag=0;
    while(lind<=rind) {
        if(flag == 0){
            if(seen.find(A[lind])!=seen.end())
                A[lind]=0;
            else
                seen.insert(A[lind]);
            lind++;
            flag = 1;
        }
        else {
            if(seen.find(A[rind])!=seen.end())
                A[rind]=0;
            else
                seen.insert(A[rind]);
            rind--;
            flag = 0;
        }
    }

    lind=0;
    rind = N-1;
    flag=0;
    for(int i =0;i<N;++i){
        if(seen.find(i)==seen.end()){
            if(flag==0){
                while(A[lind]!=0)
                    lind++;
                A[lind++]=i;
                flag = 1;
            }
            else {
                while(A[rind]!=0)
                    rind--;
                A[rind--]=i;
                flag = 0;
            }

        }
    }


    A=rotate(A,keyCum);
    return A;
}
/*********************************************************************************/

vector<vector<int> > readImg(string path) {
  Mat image;
  Vec<unsigned char, 3>  pixel;
  vector <int> red;
  vector <int> green;
  vector <int> blue;

  image = imread(path, IMREAD_COLOR );
  if ( !image.data )
  {
    cout<<"No image data \n";

  }


  rows = image.rows;
  cols = image.cols;

  for(int r = 0; r < image.rows; ++r) {
    for(int c = 0; c < image.cols; ++c) {

      pixel= image.at<Vec3b>(r,c);
      red.push_back(pixel[0]);
      green.push_back(pixel[1]);
      blue.push_back(pixel[2]);
    }
   }

  vector<vector<int> > res( 3 , vector<int> (red.size(), 0));
  res[0]= red;
  res[1]=green;
  res[2]= blue;
  return res;
}
/********************************************************/
void writeImg(string path, vector <int> red, vector <int> green, vector <int> blue){

 Mat img2(rows, cols, CV_8UC3);
 Vec<unsigned char, 3>  pixel;
 int ind = 0;
 for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {


      pixel[0] = red[ind];
      pixel[1] = green[ind];
      pixel[2] = blue[ind];
      img2.at<Vec3b>(r,c) = pixel;
      ind++;
    }
   }

   imwrite(path, img2);
   imshow(path, img2);

}

/**********************************************************/
vector<vector<int> > changeIntensity(vector<int> red,vector <int> green, vector<int>blue, vector<int> pattern,string key){

  int i,x,y,z,cumSum=0;

    for(i=0;i<key.length();++i)
        cumSum+=key[i];
    x=0;
    y=cumSum;
    z=-cumSum;

    vector<vector<int> > res( 3 , vector<int> (pattern.size(), 0));



    for(i =0; i<pattern.size();++i){
        if(pattern[i]%3==0){
            res[0][i]=((red[i]+x * pattern[i])%256+256)%256;
            res[1][i]=((green[i]+y * pattern[i])%256+256)%256;
            res[2][i]=((blue[i]+z * pattern[i])%256+256)%256;
        }
        else if(pattern[i]%3==1){
            res[0][i]=((red[i]+z * pattern[i])%256+256)%256;
            res[1][i]=((green[i]+x * pattern[i])%256+256)%256;
            res[2][i]=((blue[i]+y * pattern[i])%256+256)%256;
        }
        else {
            res[0][i]=((red[i]+y * pattern[i])%256+256)%256;
            res[1][i]=((green[i]+z * pattern[i])%256+256)%256;
            res[2][i]=((blue[i]+x * pattern[i])%256+256)%256;
        }
    }



  vector<int>pattern1 =  createPermutation(key,256);
  i=0;
  int n=pattern1.size();
  int d;
  int index1,index2,index3;
  //substitution
    while(i<pattern.size())
    {



            d=i%n;

            //rotate pattern1 by d and access indexth element
            index1=res[0][i];
            index2=res[1][i];
            index3=res[2][i];

            if(d+index1 >=n)
            res[0][i]=pattern1[index1-(n-d)];
            else
            res[0][i]=pattern1[index1+d];
            if(d+index2 >=n)
            res[1][i]=pattern1[index2-(n-d)];
            else
            res[1][i]=pattern1[index2+d];
            if(d+index3 >=n)
            res[2][i]=pattern1[index3-(n-d)];
            else
            res[2][i]=pattern1[index3+d];

            i++;



    }

  return res;

}
/*******************************************************************************************/
vector<vector<int> > revChangeIntensity(vector<int> red,vector <int> green, vector<int>blue, vector<int> pattern,string key){

  int x, y, z;
  vector<vector<int> > res( 3 , vector<int> (pattern.size(), 0));
  vector<int>pattern1 =  createPermutation(key,256);
  int i=0;
  int n=pattern1.size();
  int d;
  int cumSum=0;

    for(i=0;i<key.length();++i)
        cumSum+=key[i];
    x=0;
    y=-cumSum;
    z=cumSum;

  int i1,i2,i3;
    vector<int>::iterator it1;
    vector<int>::iterator it2;
    vector<int>::iterator it3;

  i=0;
  while(i<pattern.size())
  {


      d=i%n;
      //search for position red[i] in pattern1 rotated d times
      it1=find (pattern1.begin(), pattern1.end(),red[i]);
      it2=find (pattern1.begin(), pattern1.end(),green[i]);
      it3=find (pattern1.begin(), pattern1.end(),blue[i]);
      i1=it1-pattern1.begin();
      i2=it2-pattern1.begin();
      i3=it3-pattern1.begin();
      if(i1<d)
        red[i]=n-d+i1;
      else
        red[i]=i1-d;
      if(i2<d)
        green[i]=n-d+i2;
      else
        green[i]=i2-d;
      if(i3<d)
        blue[i]=n-d+i3;
      else
        blue[i]=i3-d;


      i++;


  }


  for(i =0; i<pattern.size();++i){
        if(pattern[i]%3==0){
            res[0][i]=((red[i]+x * pattern[i])%256+256)%256;
            res[1][i]=((green[i]+y * pattern[i])%256+256)%256;
            res[2][i]=((blue[i]+z * pattern[i])%256+256)%256;
        }
        else if(pattern[i]%3==1){
            res[0][i]=((red[i]+z * pattern[i])%256+256)%256;
            res[1][i]=((green[i]+x * pattern[i])%256+256)%256;
            res[2][i]=((blue[i]+y * pattern[i])%256+256)%256;
        }
        else {
            res[0][i]=((red[i]+y * pattern[i])%256+256)%256;
            res[1][i]=((green[i]+z * pattern[i])%256+256)%256;
            res[2][i]=((blue[i]+x * pattern[i])%256+256)%256;
        }
    }


  return res;

}



/***********************************************************/
vector<int> permute(vector<int> text, vector<int> pattern){
    vector<int> res;
    for(int i =0; i<pattern.size();++i){
        res.push_back(text[pattern[i]]);
    }
    return res;
}
/***********************************************************/
vector<int> revPermute(vector<int> text, vector<int> pattern){
    vector<int> res(pattern.size(),0);
    for(int i =0; i<pattern.size();++i){
        res[pattern[i]] = text[i];
    }
    return res;
}
/***********************************************************/
vector<vector<int> > encrypt(vector <int> red, vector <int> green, vector <int> blue, vector<int> A){

  vector<int> permR = permute(red, A);
  vector<int> permG = permute(green, A);
  vector<int> permB = permute(blue, A);

  Mat encImg(rows, cols, CV_8UC3);
  Vec<unsigned char, 3>  pixel;
  int ind=0;

  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {


      pixel[0] = permR[ind];
      pixel[1] = permG[ind];
      pixel[2] = permB[ind];

      encImg.at<Vec3b>(r,c) = pixel;
      ind++;
    }
   }

  vector<vector<int> > res ( 3 , vector<int> (red.size(), 0));
  res[0] = permR;
  res[1] = permG;
  res[2] = permB;
  return res;


}
/**********************************************************/
vector<vector<int> > decrypt(vector <int> red, vector <int> green, vector <int> blue, vector<int> A){
  vector<int> orgRed  = revPermute(red, A);
  vector<int> orgGreen= revPermute(green, A);
  vector<int> orgBlue = revPermute(blue, A);


  Mat decImg(rows, cols, CV_8UC3);
  Vec<unsigned char, 3>  pixel;
  int ind=0;

  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {


      pixel[0] = orgRed[ind];
      pixel[1] = orgGreen[ind];
      pixel[2] = orgBlue[ind];

      decImg.at<Vec3b>(r,c) = pixel;
      ind++;
    }
   }

  vector<vector<int> > res ( 3 , vector<int> (red.size(), 0));
  res[0] = orgRed;
  res[1] = orgGreen;
  res[2] = orgBlue;
  return res;

}
/***************************************************************/


void encrOpt(string pwd, string path, string fn){
  vector<vector<int> > res=readImg(path);
  vector<int>pattern =  createPermutation(pwd, rows* cols);

  vector<vector<int> > newres = changeIntensity(res[0],res[1],res[2], pattern,pwd);
  writeImg("chan.png",newres[0], newres[1],newres[2]);
  res = encrypt(newres[0], newres[1], newres[2], pattern);

  int pos=fn.find(".");
  string y=fn.substr(0,pos);
  string x="enc_"+y+".png";
  writeImg(x,res[0],res[1],res[2]);
}

void decrOpt(string pwd, string path, string fn){


  vector<vector<int> > res1=readImg(path);
  vector<int>pattern =  createPermutation(pwd, rows* cols);

  vector<vector<int> > res2=decrypt(res1[0], res1[1], res1[2], pattern);

  vector<vector<int> > newres = revChangeIntensity(res2[0],res2[1],res2[2], pattern,pwd);

  string x="dec_"+fn;
  writeImg(x,newres[0],newres[1],newres[2]);
}


