#include <fstream> // for file-access
#include <string>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <sstream>
#include <vector>
#include <cmath>


using namespace std;

struct points{
    float    x;
    float  y;
    points(float px, float py): x(px), y(py){}
};




float CalculateTheDistance(float x1 , float x2 , float y1 , float y2){
 
 float diffY = y2 - y1;
 float diffX = x2 - x1;
 return sqrt((diffY * diffY) + (diffX * diffX));
 }

bool BFS (vector <vector<float> > graph ,float distance ,int n, int s , int t , float patharray[]){
    
    bool marked[n];
    if(s==t)
    return true;
    for (int i = 0 ; i< n ; i++)
    marked[i]= false;
    
    std :: queue <int> q;
    q.push(s);
    marked[s] = true;
    patharray[s]=-1;
    
    while (!q.empty()){
        int y = q.front();
        q.pop();
        for (int i = 0 ; i < n ; i++){
            if (marked[i]==false &&graph[y][i] <= distance)
            {
                q.push(i);
                patharray[i] = y;
                marked[i] = true;
            }
        }
    }
    
    return (marked[t] == true);
}



int main(int argc, char* argv[])
{
    if (argc > 1) {
        cout << "argv[1] = " << argv[1] << endl;
    } else {
        cout << "No file name entered. Exiting...";
        return -1;
    }
  
    ifstream infile(argv[1]); //open the file

    if (infile.is_open() && infile.good()) {
        cout << "File is now open!\nContains:\n";
        string line = "";
     
        vector <string>linevec;
        while (infile>> line){
            linevec.push_back(line);
        }
        vector<string >b;
        for (int i = 0 ; i < linevec.size() ; i++){
            float len = linevec[i].length();
            b.push_back("");
            for(int j = 1 ; j< len-1 ; j++){
                
                if(linevec[i][j] != ',' ) {
                    if(b .size() == 0)
                        b[0] = b[0] + linevec[i][j];
                    else
                        b[b.size()-1]= b[b.size()-1] + linevec[i][j];
                }
                else
                    b.push_back("");
            }
        }
        
        int count = 0;

        std :: vector<points> a;
        for(int i = 0 ; i < b.size() ; i=i+2){
            
            points temp (stof(b[i]) , stof(b[i+1]) );
            a.push_back(temp);
            count ++ ;
        }
        
        vector <float >distance;
        vector<vector <float > > graph;
        vector <float > temp;
        for ( int i = 0 ; i < a.size() ; i++){
             float d ;
            for(int j = 0; j<a.size() ; j++){
           d = CalculateTheDistance(a[i].x, a[j].x ,a[i].y, a[j].y);
                distance.push_back(d);
                temp.push_back(d);
            }
            graph.push_back(temp);
            temp.clear();
        }
        
   
        for( vector<float>::iterator i = distance .begin(); i != distance.end(); ++i){
            sort(distance.begin() , distance.end());
        }
        
       float bottleneck = INT_MAX;
        float start = 0 ;
        int t = 1 ,s =0 ;
        float patharray[count];
        float end = distance.size()-1;
        int mid;
        
        while(start <= end){
            mid = (start +end)/2;
            if(BFS(graph, distance[mid], count, 0,1, patharray)){
                if(distance[mid]< bottleneck ){
                bottleneck  = distance[mid];
                    
                 }
                 end = mid -1;
                
             }
            else
                start = mid +1;
        }
        
        vector<int>result;
        for(int j = t ;j != s ; j= patharray[j])
        {
            int i= patharray [j];
            result.push_back(i);
        }
        for (int i = result.size()-1 ; i>=0 ;i--){
            cout << "(" << a[result[i]].x  <<  "," << a[result[i]].y << ")" << endl;
        }
        
        for (int j = 0 ; j <= a.size(); j= patharray[j]){
            cout << "(" << a[j+1].x << ","<<a[j+1].y << ")"<<endl;
        }
         cout << bottleneck  << endl;
        
    
    }
    else {
        cout << "Failed to open file..";
    }
    return 0;
}






