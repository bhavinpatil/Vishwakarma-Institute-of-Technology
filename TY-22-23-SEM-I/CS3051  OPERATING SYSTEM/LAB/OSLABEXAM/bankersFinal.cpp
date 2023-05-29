#include <bits/stdc++.h> 
using namespace std;

int main() { 
    int m,n;
    cout<<"Enter total number of processes:";
    cin>>m;

    cout<<"Enter total number of resources:";
    cin>>n;

    //static input
     int allocation[5][4] = {{4, 0, 0, 1}, 
                            {1, 1, 0, 0}, 
                            {1, 2, 5, 4},
                            {0, 6, 3, 3}, 
                            {0, 2, 1, 2}};
    
    int max[5][4] = {   {6, 0, 1, 2},   
                        {2, 7, 5, 0},  
                        {2, 3, 5, 6},  
                        {1, 6, 5, 3},  
                        {1, 6, 5, 6}}; 

    int available[4] = {3, 2, 1, 1};
    
    //static input
    /*int allocation[5][3] = {{0, 1, 0},   
                        {2, 0, 0},  
                        {3, 0, 2},  
                        {2, 1, 1},  
                        {0, 0, 2}}; 
  
    int max[5][3] = {{7, 5, 3}, 
                      {3, 2, 2}, 
                      {9, 0, 2}, 
                      {2, 2, 2}, 
                      {4, 3, 3}}; 

    int available[3] = {3, 3, 2}; 
    */

    //dynamic input
    /*
    int max[m][n];
    cout<<"\nEnter max resources for each process:\n";
    for(int i=0;i<m;i++)
    {
        cout<<"Enter for process "<<i+1<<":";
        for(int j=0;j<n;j++)
        {
            cin>>max[i][j];
        }
    }

    int allocation[m][n];
    cout<<"\nEnter allocation resources for each process:\n";
    for(int i=0;i<m;i++)
    {
        cout<<"Enter for process "<<i+1<<":";
        for(int j=0;j<n;j++)
        {
            cin>>allocation[i][j];
        }
    }

    int available[n]; 
    cout<<"\nEnter available resources: ";
    for(int i=0;i<n;i++)
    {
            cin>>available[i];
    }
    */

    int finish[m] = {0};
    int ans[m] = {0};
    int idx =  0; 
    
    int need[m][n];  
    for(int i=0;i<m;i++)
    { 
        for(int j=0;j<n; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        } 
    } 

    cout<<"Processes";
    cout<<"\tMax";
    cout<<"\t\tAllocation";
    cout<<"\tNeed";
    for(int i=0;i<m;i++)
    {
    cout<<"\n   P"<<i;
    cout<<"\t\t";
    for(int j=0;j<n;j++)
    {
        cout<<max[i][j]<<" ";
    }
    cout<<"\t";
    for(int j=0;j<n;j++)
    {
        cout<<allocation[i][j]<<" ";
    }
    cout<<"\t";
    for(int j=0;j<n;j++)
    {
        cout<<need[i][j]<<" ";
    }
    cout<<"\n";
    }
    int y = 0; 
    for (int k=0;k<m;k++) 
    { 
        for(int i=0;i<m;i++)
        { 
            if(finish[i]==0)
            { 
                int flag = 0; 
                for(int j=0;j<n;j++)
                { 
                    if(need[i][j]>available[j])
                    { 
                        flag = 1; 
                        break; 
                    }
                } 

                if(flag==0)
                {  
                    ans[idx++] = i; 
                    for(int y=0;y<n;y++)
                    { 
                        available[y] += allocation[i][y]; 
                    }
                    finish[i] = 1; 
                    cout<<"\nResources are allocated to P"<<i;
                    cout<<"\nNow resources are deallocated";
                    cout<<"\nNew availability:";
                    for(int i=0;i<n;i++)
                    {
                        cout<<available[i]<<" ";
                    }
                    cout<<"\n";
                } 
            } 
        } 
    } 
    
    bool flag = true;
    for(int i=0; i<m; i++)
    {
        if(finish[i] == 0)
        { 
            flag = false; 
            cout<<"\nSystem is in deadlock !!"; 
            break; 
        }
    }
    
    if(flag==true)
    {
        cout<<"\nSystem is in safe state and following is the safe sequence: ";
        for(int i=0;i<m-1;i++)
        {
            cout<<"P"<<ans[i]<<" -> "; 
        }
        cout<<"P"<<ans[m-1]<<endl;
    }  
    return 0; 
} 
