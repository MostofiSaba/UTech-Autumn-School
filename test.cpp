#include<iostream>
#include<conio.h>
#include <cstdlib>
#include <math.h>
#include <vector> 
#include <list> 
#include <iterator> 
#include<unordered_map>
#include <algorithm>

using namespace std;

// This code simulates a cache mamory

class Algorithme{
	
	public:
	
	vector<int> fifo(){
		vector<int> vec;
		int u =0;
		while(u < 30){
		for(int i = 0; i < 4; i++){
			vec.push_back(i) ;
		}
		u++;
		}
		
		return vec;
	}
};

class Lru{
	
	public:
		
		int capacity;
		int hit = 0;
		list<int> keys;
		unordered_map<int,pair<int,list<int>::iterator>> map;
		Lru(int cap){
			
			capacity = cap;
		}
	
		
	 	void put(int key, int value){
		
			if(map.find(key) != map.end()){
		 		keys.erase(map[key].second);
		 		keys.push_front(key);
		 		map[key] = {value,keys.begin()};
		 		hit ++ ;
			}else{
				if(keys.size() == capacity){
					map.erase(keys.back());
					keys.pop_back();
				}
				keys.push_front(key);
				map[key] = {value, keys.begin()};
			}
		}
};



class CPU{
	
	public:
		
	   vector<int> addres; 
	   vector<int> address;
	   
	 
	 
     void random_add(int mem_size){
		
		for (int i= 0; i< 30; i++){
			addres.push_back(rand() % mem_size);
		};
		address = addres;
	
	 }

};



class Cache{
	
	public:
		
		int tag[4] ;
		int valid[4] ;
		
};

class CCU{
	
	public :
		
		vector<int> block_num;
		vector<int> word_in_block;
		vector<int> block_in_cache;
		list<int> way0 ;
		list<int> way1;
		int count0 = 0;
		int count1 = 0;
		int hit = 0;
		int flag[30] = {0};
		int set_num[30];
		
		void cal_dir(vector<int> a, int b){
			
			for(int j = 0; j<30; j++){
				block_num.push_back(a[j] / b);
				word_in_block.push_back(a[j] % b);
				block_in_cache.push_back(block_num[j] % b);
			};
			
		
		}
		
		void cal_fully(vector<int> a, int b){
			
			for(int j = 0; j<30; j++){
				block_num.push_back(a[j] / b);
				word_in_block.push_back(a[j] % b);
				};
		}
		
		void cal_way(vector<int> a){
			
			for(int l=0; l<30; l++){
				if(a[l]%2 == 0)
					set_num[l] = 0;
				else
					set_num[l] = 1;
			}
			
		}
		
		
		
		double tag(int m , int n){
			double x = m/n;
			double result = log2(x);
			return result;
		}
		
		
		void find_dir(int v[],int t[],int b_c, int tag ){
		
			if(v[b_c] == 1){
				if(t[b_c] == tag){
					hit ++;
				}
				else{
					t[b_c] = tag;
				}
				
			
			}
			else{
				v[b_c] = 1;
				t[b_c] = tag;
			}
		}
		
		void find_fully_f(int v[],int t[],int b_c, int tag, int counter ){
			
			
		
			if(v[b_c] == 1){
				for(int e=0; e<4; e++){
					if(t[e] == tag){
						flag[counter + 1] = 1;
						hit ++;
						break;}
					}
					
				t[b_c] = tag;
				flag[counter] = 0;	
			}
			else{
				v[b_c] = 1;
				t[b_c] = tag;
				flag[counter] = 0;
			}
		}
			
			int find_fully_l(int t[],int b_c, int tag){

				int hit =0;
				t[b_c] = tag;
				if(b_c == 0){
				hit ++;	
				}
				return hit; 
					
			}
			void find_way(int w, int tg){
			
				
					if(w == 0){
						
						way0.push_back(tg);
						count0 ++;
						
					}else if(w == 1){
						
						way1.push_back(tg);
						count1 ++;
					}
						
			}
			
			
		
		
};


int main()
{
	cout<<"We CAN do it."<<endl;
	int type;
	int algorithme;
	int binaryNum[32];
	int ctag_dir[64];
	int ctag_fully[64];
	int ctag_way[64];
	CPU cpu;
	cpu.random_add(64);
	CCU c;
	Cache cache;
	Algorithme al;
	cout<<"Enter the number of your cache type:(direct= 0 / fully-associative = 1 / 2_way = 2 )"<<endl;
	cin>>type;
	if(type == 1 || type == 2){
	cout<<"Enter the number of your algorithme:(FIFO = 0 / LRU = 1 )"<<endl;
	cin>>algorithme;
	}
	if(type == 0){
	
		c.cal_dir(cpu.addres,4);
		int tag_dir = c.tag(64,16);	
	
	for(int x = 0; x < 30; x++)
	{
		int i = 0;
		int n = 0;
		int base = 1;
		int dec_value_dir = 0;
		
		while (cpu.address[x] > 0){ 
			binaryNum[i] = cpu.address[x] % 2; 
			
       		cpu.address[x] = int(cpu.address[x] / 2); 
        	i++;
        	
        	
		};
		
		while(i< 6){
			
			binaryNum[i] = 0;
			i++;
		}

   		while(n<tag_dir){
    	 	dec_value_dir += binaryNum[i-2] * base;
			base = base * 2;
			i++;
			n++;
			}
			
		ctag_dir[x] = dec_value_dir;
			
	};
	
	for(int s = 0; s<30; s++){
    	c.find_dir(cache.valid,cache.tag,c.block_in_cache[s],ctag_dir[s]);
    }
	
	for(int w = 0; w < 30; w++){
		
		cout<<"address: "<<cpu.addres[w]<<endl;
		cout<<"___________ "<<endl;
		
		
	}
	cout<<"hit rate: "<<c.hit<<endl;
		
	}
	else if (type == 1)
	{
		if(algorithme == 0)
		{
			
			c.cal_fully(cpu.addres,4);
			int tag_fully = c.tag(64,4);
			vector<int> blk;
			blk = al.fifo();
			
			
			for(int x = 0; x < 30; x++)
			{
				int i = 0;
				int n = 0;
				int base = 1;
				int dec_value_fully = 0;
		
				while (cpu.address[x] > 0){ 
					binaryNum[i] = cpu.address[x] % 2;
					cpu.address[x] = int(cpu.address[x] / 2); 
        			i++;
  				}; 
		
				while(i< 6){
			
					binaryNum[i] = 0;
					i++;
				}

   				while(n<tag_fully){
    	 			dec_value_fully += binaryNum[i-4] * base;
					base = base * 2;
					i++;
					n++;
				}
				ctag_fully[x] = dec_value_fully;
				
			};
			
			
			
			for(int m = 0; m<30 ;m++){
					c.find_fully_f(cache.valid,cache.tag,blk[m ],ctag_fully[m],m);
					
					if(c.flag[m] == 1){
						cout<<"entered"<<endl;
						c.find_fully_f(cache.valid,cache.tag,blk[m -1],ctag_fully[m],m);
					}
			}
			
    		
    		for(int w = 0; w < 30; w++){
				cout<<"address: "<<cpu.addres[w]<<endl;
				cout<<"___________ "<<endl;
			}
			cout<<"hit rate: "<<c.hit<<endl;
		}
		
		else if(algorithme == 1)
		{
			
			Lru lru(4);
			int tag_fully = c.tag(64,4);
			for(int x = 0; x < 30; x++)
			{
				int i = 0;
				int n = 0;
				int base = 1;
				int dec_value_fully = 0;
		
				while (cpu.address[x] > 0){ 
					binaryNum[i] = cpu.address[x] % 2;
					cpu.address[x] = int(cpu.address[x] / 2); 
        			i++;
  				}; 
		
				while(i< 6){
			
					binaryNum[i] = 0;
					i++;
				}

   				while(n<tag_fully){
    	 			dec_value_fully += binaryNum[i-4] * base;
					base = base * 2;
					i++;
					n++;
				}
				ctag_fully[x] = dec_value_fully;
				
			};
			
			for(int y = 0; y < 30; y++){
				lru.put(ctag_fully[y],cpu.address[y]);
				cout<<"address: "<<cpu.addres[y]<<endl;
				cout<<"___________ "<<endl;
			};
			
			cout<<"hit rate: "<<lru.hit<<endl;
	}
			
	}
	
	else if(type == 2){
		
		int tag_way = c.tag(64,8);
		for(int x = 0; x < 30; x++)
			{
				int i = 0;
				int n = 0;
				int base = 1;
				int dec_value_way = 0;
		
				while (cpu.address[x] > 0){ 
					binaryNum[i] = cpu.address[x] % 2;
					cpu.address[x] = int(cpu.address[x] / 2); 
        			i++;
  				}; 
		
				while(i< 6){
			
					binaryNum[i] = 0;
					i++;
				}

   				while(n<tag_way){
    	 			dec_value_way += binaryNum[i-3] * base;
    	 			base = base * 2;
					i++;
					n++;
				}
				ctag_way[x] = dec_value_way;
				
				
			};
		c.cal_way(cpu.addres);
		for(int d=0; d<30; d++){
			c.find_way(c.set_num[d],ctag_way[d]);
		}
		
		Lru lru(2);
		
		for(auto it = c.way0.begin(); it != c.way0.end(); it++){
			lru.put(*it,1);
			}
		int hit_rate = lru.hit;
		Lru lru1(2);
		for(auto ito = c.way1.begin(); ito != c.way1.end(); ito++){
			lru1.put(*ito,1);
		}
		hit_rate += lru1.hit;
		cout<<"hit rate: "<<hit_rate<<endl;
	}
	
	return 0;
}
	
	
	
	
	

