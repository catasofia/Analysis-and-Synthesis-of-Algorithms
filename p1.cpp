
#include <iostream>
#include <list> 

using namespace std;

class Vertex{
  private:
		int _id;
    int _discoveryTime;
    int _testValue;
    int _parentId;
    int color;
		list <Vertex> _friends;
    
  public:
		Vertex(){
				_discoveryTime = -1;
				_parentId = -1;
		}

		int getDiscoveryTime(){
				return _discoveryTime;
		}

		void setDiscoveryTime(int discoveryTime){
				_discoveryTime = discoveryTime;
		}

		void addFriend(Vertex vertex){
			_friends.push_back(vertex);
		}


	/* int main(){
		return 0;
	} */
};