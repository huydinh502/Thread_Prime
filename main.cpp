#include <iostream>
#include <cstdlib>
#include <thread>
#include<vector>
#include <algorithm> // unique, sort
using namespace std;

void Findprime(int a, int b, vector<int>& prime) // mau chuan cua than ham trong thread
{
     for(int i=a; i<=b; i++)
     {   int count{0};
         if(i>=2)
         {
             for(int j=2;j<i;j++ )
            {
                if(i%j == 0)
                {
                 count+=1;
                }
            }
            if(count==0)
            prime.push_back(i);
         }
     }
}

void Wait(vector<thread>& th, int m,vector<int>& prime)
{
        for(int i= 0; i<m; i++)
      {
         th[i].join();
      }
      sort(prime.begin(), prime.end() ); // sap xep truoc khi xoa trung

      prime.erase( unique( prime.begin(), prime.end() ), prime.end() ); // xoa cac phan tu trung nhau

      cout << "Tong so nguyen to la: "<<prime.size();

}

int main ()
{
    int n,m;
    vector<int> prime;  // vector chua cac so nguyen to
    vector<thread> th; // vector chua cac Thread

    cout <<"Input n: ";
    cin >> n;
    cout <<"Input m: ";
    cin >> m;

    for(int i=0; i <= m; i++)
    {
        if(i==0)
        {
           th.push_back(std::thread(Findprime,1, n/m, ref(prime)));
        }
        else if(i==m)
        {
           th.push_back(std::thread(Wait, ref(th), m, ref(prime))); // Thread m chờ cac Thread tu 0 den m-1
         }
        else{
           th.push_back(thread(Findprime, i*n/m, (i+1)*n/m, ref(prime)));
        }

    }
    th[m].join();
   return 0;
}
