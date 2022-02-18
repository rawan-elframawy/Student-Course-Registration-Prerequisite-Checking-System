/*
Rawan Elfaramawy 202001762
Mariam Barakat 202000210
Noreen Gamal 202000594
Yara Mahfouz 202001787
*/
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
#include <vector>
#include <algorithm>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
//#include <graphics.h>

using namespace std;

// extracts first 3 numbers (course code) from a given word
int extractCode(string& w)
{
    char s[3];
    for (int i = 0; i < 3; i++)
    {
        if (!isdigit(w[i]))
            return 0;
        s[i] = w[i];
    }
    string str(s);
    return stoi(s);
}
//============================================== Classes ========================================================================
//============================= Content Class
class Content
{
    public:
    // this is an array that stores the elements in the text file
    // if the file has more than 11 lines, this part must be changed, as it is not dynamic
	int courses[11][2];

	void contentTransfer()
	{
		// create file object
		fstream coursesFile;
		// open file in read mode
		coursesFile.open("Courses.csv", ios::in);
		string line, word;
		// check if file has opened successfully
		if (coursesFile.is_open())
		{
			int index = 0;
			// extracting each line of the file untill getline returns NULL
			while (getline(coursesFile, line))
			{
				// converting line (type string) to a filestream-like object to be able to use it as a parameter in getline
				stringstream L(line);
				// loop for storing codes
				for (int i = 0; i < 2; i++)
				{
					// splitting line to words
					getline(L, word, ',');
					// extracting code from each word then storing it to an array
					courses[index][i] = extractCode(word);
				}
				index++;
			}
		}
		else
			cout << "could not open the file" << endl;
	}

	// returns element from courses array at specific indices
	int getCode(int x, int y)
	{
		return courses[x][y];
	}
};
//=========================== Class of the binary tree
// A tree is represented by a pointer to the topmost node in tree. If the tree is empty, then value of root is NULL.
/*
A Tree node contains following parts.
1- Data : value of each node.
2- Node Pointer to left child (Node).
3- Node Pointer to right child (Node).
*/
class BT{
public:
	struct Node{
	    // Data of every node
		int data;
		// Left and right child for each node
		Node* left;
		Node* right;
		Node(int value){
			data = value;
			left = right = NULL;
		}
	};
	Node* root = NULL;
//---------------------------------------------------------------------------------------
    // Aim of this function : Find the correct position of the new node [The Course], then insert it.
    // Parameters : temp (node) , value [The new course] , pre [The prerequisite of the new course]
    // Type of the function : Boolean.
    // What is the base case (When function stop) :
       // 1- If we find the search node [Node of prerequisite course] through checking node value .
       // 2- When the temp node is null (reach the leaves of the tree) ,Thats mean that we did not find the search node.
    // How this function work ?
    /*
    The idea of the this function is traverse (Pre-Order) the tree through recursion :
      1- Check the root.
      2- Traverse the left sub-tree.
      3- Traverse the right sub-tree.
    */
    // - In each traverse we check if the value of " pre variable " [The prerequisite course] matched with the value of "temp node" [The current node] .
    // If yes :
       // 1- Then the function return TRUE.
       // 2- This means the The prerequisite course was found in the left sub-tree.
       // 3- No need to traverse the rest of the tree.

    // If No :
       // 1- Function return FALSE.
       // 2- Then the function will traverse the right sub-tree through recursion till find it.
       // 3- If the search node found the return TRUE.
       // 4- No need to traverse the rest of the tree.
       // 5- If Not, the the whole function will return FALSE.
    void BFT(struct Node* root)  // breadth first traversal
    {
       queue<Node*> q;
        if (!root) {
            return;
        }
        for (q.push(root); !q.empty(); q.pop()) {
            const Node *temp_node = q.front();
            cout<<temp_node->data << " ";

            if (temp_node->left) {
                q.push(temp_node->left);
            }
            if (temp_node->right) {
                q.push(temp_node->right);
            }
        }
    }
    void BFT2(struct Node* root, vector<int>&a)  // breadth first traversal
    {
       queue<Node*> q; // this is a q that stores the pointers of Node
        if (!root) { // returns if there is not root aslan
            return;
        }
        for (q.push(root); !q.empty(); q.pop()) {   // will add nodes to a vector in the level by level format
            const Node *temp_node = q.front();
            a.push_back(temp_node->data);

            if (temp_node->left) {
                q.push(temp_node->left);
            }
            if (temp_node->right) {
                q.push(temp_node->right);
            }
        }
    }
	bool addHelper(Node* temp, int value, int pre){
	    // Reach the end of sub-tree.
		if (temp == NULL)
        return false;
        // If the search node is found
        if (temp->data == pre){
            // Check if the right and the left of search node is NULL.
            if (temp->right == NULL && temp->left == NULL){
                // Insert the new node [new course] in the left of the search node [Its prerequisite].
                temp-> left = new Node(value);
                // End the recursion
                return true;
            }
            // Check if only the right of search node is NULL.
            else if(temp->right == NULL && temp->left != NULL){
                // Insert the new node [new course] in the left of the search node [Its prerequisite].
                temp-> right = new Node(value);
                // End the recursion
                return true;
            }
        }
      bool foundLeft = addHelper(temp->left, value ,pre);
      if(foundLeft) return true;
      // Traverse the right sub-tree
      bool foundRight = addHelper(temp->right, value ,pre);
      return foundRight;
	}
	void add(int value, int pre){
	    // If it is the first node (root node)
		if (root == NULL){
			root = new Node(value);
        }
		else{
            // Function that add node.
			addHelper(root, value, pre);
		}
	}
    // a member function, where we input the root and the target, it finds the target and stores
    // all its ancestors in a vector a
    bool ancestors( Node *root ,int target, vector<int>& a)
    {
        // base step 1 reached when there is no more nodes, and still didnt find the target
        if(root == 0)
            return false;
        // base step 2 reached when finally found the value, so returns true and stops
        if(root->data == target)
            return true;
        // recursive step, it recursively searches in the left and the right branches and added to the
        // vector the ancestor of the target (only happens when return true)
        if(ancestors(root->left, target,a) || ancestors(root->right, target,a) == true)
        {
            if(root->data != 0)
                a.push_back(root->data);
            return true;
        }
        // returns false otherwise
        return false;

    }
    bool ifNodeExists( Node *node , int key)
{
    if (node == NULL)
        return false;
    if (node->data == key)
        return true;
    /* then recur on left subtree */
    bool res1 = ifNodeExists(node->left, key);
    // node found, no need to look further
    if(res1) return true;
    /* node is not found in left,
    so recur on right subtree */
    bool res2 = ifNodeExists(node->right, key);
    return res2;
}
// adds zero when the children are not found and there is one left or right
//this creates a full binary tree
void zero_padding(struct Node* node, int c=0)
{
    if (node == NULL)  // when the node has nothing
        return;
    if((node->left== NULL) && (node->right == NULL)) // when the nodes don't have left nor right
    {
        node->left= new Node(0);
        node->right = new Node(0);
        c++;              // the c allows us to track the level we reached so that we don't have a non-terminating loop
    }
    if(node->left == NULL)
    {
        node->left = new Node(0);
        c++;
    }
    if(node->right == NULL)
    {
        node->right = new Node(0);
        c++;
    }
    if(c== 4)
    {
        return;
    }
    /* then recur on left subtree */
    zero_padding(node->left,c);

    /* now recur on right subtree */
    zero_padding(node->right,c);
}
// This function take 4 parameters , the only one parameter that need change in calling is the first parameter => make it the root of student tree
// So there is nothing need change in this function , the change only in calling
//------------------------------------------------------------------------------------------------------------------
    // Aim of this function : Find num of child nodes for each node given , so we can draw num lines between nodes correctly.
    // Parameters : temp (root of student tree) , value (course code) , found (0=> we find the course, 1=> we did not find the course) , x (num of child nodes for each node given)
    // Type of the function : void.
    // What is the base case (When function stop) :
       // 1- If we find the search node [Node of prerequisite course] through checking node value .
       // 2- When the temp node is null (reach the leaves of the tree) ,Thats mean that we did not find the search node.
    // How this function work ?
	   /*
	    The idea of the this function is traverse (Pre-Order) the tree through recursion :
	      1- Check the root.
	      2- Traverse the left sub-tree.
	      3- Traverse the right sub-tree.
	    */
	    // - In each traverse we check if the value of " course " matched with the value of "temp node" [The current node] .
	       // 1 - I YES => Then check num of child nodes for this node.
		        // - x => 3 , if there is 2 child nodes , then we shound draw 2 lines for this node.
				// - x => 2 , if there is only 1 child node. [LEFT node] , then we shound draw only 1 left line for this node.
				// - x => 1 , if there is only 1 child node. [RIGHT node] , then we shound draw only 1 right line for this node.
			// 2 - If NO => continue recursion until reaching leveas of right sub-tree.
	void numChildNodes(Node* temp, int value, int found, int *x){

		// Reach the end of sub-tree.
		if (temp == NULL)
        return;
        // If the search node is found
        if (temp->data == value){
        	// We reach our goal, then found = 1, so no need for more recursion
        	found =1;

            // Check if the right and the left of search node is NULL or zero.
            if ((temp->left != NULL && temp->left->data !=0) && (temp->right != NULL && temp->right->data !=0) ){
            	*x = 3;

            }
            // Check if the right of search node is NULL or a zero.
            else if ((temp->left != NULL && temp->left->data !=0) && (temp->right == NULL || temp->right->data == 0)){
            	*x = 2;

			}
			// Check if the left of search node is NULL or a zero.
			else if ((temp->left == NULL || temp->left->data==0) && (temp->right != NULL && temp->right->data !=0)) {
				*x = 1;

			}
			return;
        }
        // recursion over the left sub-tree
      numChildNodes(temp->left, value,found,x);
      if(!found) {
      	// recursion over the right sub-tree
        numChildNodes(temp->right, value,found,x);
	  }
	  else{
	  	return;
	  }
}
/*
// GRAPHICAL REPRESENTATION
	void tree_graph(int x, int y, int* array, int index, int total_elements){
		// z => express number of child nodes for evey node
		int z =0;
		// Base Case : we finish looping over all array elements.
	    if (index >= total_elements)
	        return;
	    // Convert int value into string.
	    ostringstream str1;
	    str1 << array[index];
	    string str2 = str1.str();
	    char* str = &str2[0u];
	    if (array[index]!=0){
		    // Set color of the boundary of circle as green.
		    setcolor(GREEN);
		    // Draw the circle of radius 15 that represent node of Tree.
		    circle(x, y, 15);
		    floodfill(x, y, GREEN);
		    // Print the values of the node in the circle.
		    outtextxy(x - 2, y - 3, str);
		    // Set the color of the line from parent to child as green.
		    setcolor(GREEN);
	    }
	    // Evaluating left and right child
	    int left = 2 * index + 1;
	    int right = 2 * index + 2;
	    // Draw the left subtree and the right subtree using recursion
	    tree_graph(x - y / (index + 1), y + 50,array, left, total_elements);
	    tree_graph(x + y / (index + 1), y + 50, array, right, total_elements);
	     // check num of child nodes
	    numChildNodes(root ,array[index],0,&z);
	    // Draw the line (or link) between 2 nodes
	    if (array[index] != 0){
	    	// Check if the node has 2 child
	    	if (z == 3){
	    		// Draw right and left line
	    		if (left < total_elements) {
		        	line(x, y, x - y / (index + 1), y + 50);
		    	}
	            	if (right < total_elements) {
						line(x, y, x + y / (index + 1), y + 50);
				    }
			}
			// Check if the node has only left child
			else if (z == 2){
				if (left < total_elements) {
					// Draw only the left line
		        	line(x, y, x - y / (index + 1), y + 50);
		    	}
			}
			// Check if the node has only right child
	    	else if (z == 1){
            	if (right < total_elements) {
            		// Draw only the right line
					line(x, y, x + y / (index + 1), y + 50);
			    }
			}
		}
		return;
    }
    */
};
// ================================================ functions =======================================================
bool found(int a, vector<int> c)
{
    // search for the element a in vector c
    for(int i=0; i< c.size(); i++)
    {
        if(c[i]== a)
            return true;
    }
    return false;
}

// Check if course is taken or not
bool takenOrNot(vector<int>& vect , int temp_course_code ,int n){
    for (int i = 0; i <  n; i++){
        if (temp_course_code == vect[i]){
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------
vector<int> graph_student(vector<int> took, vector<int> can, Content Test, BT &obj2)
{
    // 1- have an array with all the needed subjects to create a tree
    // 2- move through the txt file
    // 3- create the tree
    can.insert(can.end(), took.begin(), took.end());
    for (int i = 0; i < 11; i++)
	{
	    // First Argument: The code of the course
	    // Second Argument: The code of the prerequisite course.
	    if(found(Test.courses[i][0], can)== true)
            obj2.add(Test.getCode(i, 0),Test.getCode(i, 1));
	}
	// add zeroes to the nodes
	obj2.zero_padding(obj2.root);
	vector<int> answer;
	obj2.BFT2(obj2.root, answer);
// changed to vector to be able to pass the vector to the main
	return answer;
}
// this is a function that takes the vector containing what the student took and what he wants to take
// it iterates through each of the subjects the student wants to take
// then makes sure that all its prereq are taken by the student, if not will add it to the cannot vector , if it was found then will add to the can vector
vector<int> topological(vector<int>take, vector<int>took, BT T , string s[], int arr_size, Content Test, BT &obj2)
{
    // local variables, they are vectors to store the can and connt take courses codes
    vector<int> can;
    vector<int> cannot;
    // a loop that iterates through all the subjects the student wants to take and makes sure if all the prereq are there
    for(int i=0; i < take.size(); i++)
    {
        // vector that stores the needed prereq for the subject the student wants to take
        vector<int> temp;
        T.ancestors(T.root, take[i], temp); // temp will have the subjects that the student must have taken
        // search whether the student took all or not
        bool flag = true; // a flag to allow us know if all the prereq are there or not
        for(int j=0; j< temp.size(); j++)
        {
            if (find(took.begin(), took.end(), temp[j] ) != took.end() ) // find is an algorithm that is built in, it sees if the given item is in the vector or not
               continue;
            else
            {
                cannot.push_back(take[i]); // sure that one of the prereq not there, so will add to cannot
                flag = false; // to not confuse with the can
                break;
            }
        }
        if(flag == true)  // flag is only truly true when all the prereq are found
            can.push_back(take[i]);
    }
    cout <<"The following courses are OK to take: "<<endl;
    for(int i=0; i< can.size(); i++)
    {
        for(int j=0; j< arr_size; j++)
        {
            int n = extractCode(s[j]);
            if(can[i] == n)
                cout << s[j] << endl;
        }
    }
    cout << endl;
    cout <<"The following courses cannot be taken: "<<endl;
     for(int i=0; i< cannot.size(); i++)
    {
        for(int j=0; j< arr_size; j++)
        {
            int n = extractCode(s[j]);
            if(cannot[i] == n)
                cout << s[j] << endl;
        }
    }
    cout << endl;
// changed to vector to be able to pass the vector to the main
    vector<int> answer1= graph_student(took,can,Test, obj2);
    return answer1;
}
vector<int> execution(BT obj, Content Test, BT &obj2)
{
   //======================= user input =============================
     // variable names and containers
      vector<int> courses_taken;
      vector<int> courses_to_take;
      int number_of_courses_taken;
      int number_of_courses_to_take;
      string temp_course_name;
      int temp_course_code;
      //----------------------------------user interface
      // courses taken
      cout << "How many courses have you already studied?\n"<< endl;
      cin >> number_of_courses_taken;
      cout << "Enter the courses which you already studied:\n"<< endl;
      for(int i=0; i<number_of_courses_taken; i++)
      {
          cout << "Course "<< i+1<< "  ";
          cin>> temp_course_name;
          cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this was used to clear the \n from missing with the string
          temp_course_code = extractCode(temp_course_name);
          while(!(obj.ifNodeExists(obj.root, temp_course_code)) || !extractCode(temp_course_name))
          {
              cout <<"This course is not available or invalid name . . ."<< endl;
              cout << "Course "<< i+1<< "  ";
              cin>> temp_course_name;
              cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this was used to clear the \n from missing with the string
              temp_course_code = extractCode(temp_course_name);
          }
          courses_taken.push_back(temp_course_code);
      }
      // courses to take
      cout <<"How many courses do you want to take this semester?\n"<< endl;
      cin >> number_of_courses_to_take;
      string to_take[number_of_courses_to_take]; // used so that at printing we have the full name maintained
      cout << "Enter the courses that you want to study:\n" << endl;
      cin.ignore();
      for(int i=0; i<number_of_courses_to_take; i++)
      {
          cout<< "Course "<<i+1<< "  ";
          //cin>> temp_course_name;
         getline(cin, temp_course_name);
          to_take[i]=temp_course_name;
         temp_course_code = extractCode(temp_course_name);

         while(!(obj.ifNodeExists(obj.root, temp_course_code)) || !extractCode(temp_course_name) || takenOrNot(courses_taken,temp_course_code,courses_taken.size()))
         {
            if (takenOrNot(courses_taken,temp_course_code,courses_taken.size())){
                cout << "You have taken this course before" << endl;
            }
            else{
                cout <<"This course is not available or invalid name . . ."<< endl;
            }
            cout<< "Course "<<i+1<< "  ";
            //cin>> temp_course_name;
            getline(cin, temp_course_name);
            to_take[i]=temp_course_name;
            temp_course_code = extractCode(temp_course_name);
         }
        courses_to_take.push_back(temp_course_code);
      }
    //---------------------------- top sort and output response
    cout <<endl;
    cout << "Processing. . . .\n"<<endl;
    // changed to vector to be able to pass the vector to the main
    vector<int> a=topological(courses_to_take, courses_taken, obj,to_take, number_of_courses_to_take, Test, obj2);
    return a;

}
//======================================= driver code ===============================================================
int main( )
{
    cout << "\t======================== WELCOME TO STUDENT'S REGISTRATION ========================\n"<< endl;
	Content test;
	test.contentTransfer();
	BT obj;
	//--------------------------------
	// Loop over the 2d array to insert every course in the tree.
	for (int i = 0; i < 11; i++)
	{
	    // First Argument: The code of the course
	    // Second Argument: The code of the prerequisite course.
	    obj.add(test.getCode(i, 0),test.getCode(i, 1));
	}
	BT obj2;
    vector<int> answer= execution(obj, test,obj2);
    /*
    // graphical interface
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "None");
    */
    int n= answer.size();
    // Given array arr[]

    int array [n];
    for(int i=0; i<n; i++)
    {
        array[i]= answer[i];
    }
    /*
    // Function Call
    obj2.tree_graph(300, 100, array, 0, sizeof(array)/sizeof(array[0]));
    getch();
    closegraph();
	return 0;
	*/
}
