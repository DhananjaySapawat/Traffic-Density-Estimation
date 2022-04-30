#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
long int error(double a,double b){
      long double c = abs(a-b);
      c = c/a ;
      c = c*100000;
      long int d = (long int)c ;
      return d ;
}
int GiveNo(string a){
    int b = 0;
    for (int i = 0;i<a.size();i++){
        int m = a[i] - '0';
        if(m<10){
            b = i;
            break;
        }
    }
    int c = a.size() -4;
    int d = stoi(a.substr(b,c-b));
    return d;
}
int main(int argc, char* argv[]){
    if(argc!=2){
        cout<<"Error: ";
        return -1;
    }
  string BaseFile = "analysis/baseline.txt";
  string FileName = argv[1]; 
  string File ;
  string errorout;
  if(FileName.substr(6,2)=="su"){
       File = "analysis/SubSampling/"+FileName;
       errorout = "analysis/SubSampling/SubSamplingError.txt";
  }
  else if(FileName.substr(6,2)=="te"){
       File = "analysis/Temporal/"+FileName;
       errorout = "analysis/Temporal/TemporalError.txt";
  }
  else if(FileName.substr(6,2)=="sp"){
       File = "analysis/Spatial/"+FileName;
       errorout = "analysis/Spatial/SpatialError.txt";
  }
  else if(FileName.substr(6,2)=="re"){
       File = "analysis/Resolution/"+FileName;
       errorout = "analysis/Resolution/ResolutionError.txt";
  }
  string Density1;
  string Density2;
  // Read from the text file
  fstream myOutfile;
  myOutfile.open ("Error.txt", fstream::app);
  ifstream MyReadFile1(BaseFile);
  ifstream MyReadFile2(File);
  // Use a while loop together with the getline() function to read the file line by line
  int answer = 0 ;
  int frameNum = 0 ;
  double sub = 0;
  while (getline (MyReadFile1, Density1)&&getline (MyReadFile2, Density2)) {
        frameNum++; 
        int i = 0;
        while(Density1[i]!=','){
              i++;
            }

        int j = 0;
        while(Density2[j]!=','){
              j++;
            }
        double a = stod(Density1.substr(i+1));
        double b = stod(Density2.substr(j+1));
        if(frameNum == 2){
            a = 0 ;
        }
        answer = answer+error(a,b);
  }
  long double answer2 = ( long double)answer;
  answer2 = answer/(1.0*(100000));
  answer2 = answer2*100.00;
  answer2 = answer2/(1.0*frameNum);
  // Close the file
  MyReadFile1.close();
  MyReadFile2.close();
  myOutfile<<FileName<<" Error"<<":"<< answer2 <<endl;
  myOutfile.close();
  fstream out;
  out.open(errorout, ios::out | ios::app);
  int no = GiveNo(FileName);
  out<< no<<","<<answer2 <<endl;
  out.close();

}
