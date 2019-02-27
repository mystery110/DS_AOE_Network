Variable 
-)Since it is a directed graph , each vertex will has a header struct and multiple Node struct of it's head
  a)Header struct
    -)int tail:To record the key value of this vertex
    -)int count:To record how many tail it has
    -)Node_Pointer Next:Points toward it's head
  b)Node struct
    -)int head:To record the key value of this vertex
    -)int distance:To record the cost of the activity from header to this node struct.
    -)Node_Pointer Next:Points toward next head of the header
  c)Acticity struct
    -)int index:To record which activity this is 
    -)int head & int tail:To record the head and tail of this edge
    -)Activity_Pointer Next_Activity points toward the next activity .

-)initial_Activity is a linked-list that linked add the Activity struct together

-)int no_Edge & no_Event record the total number of edge and event exist.

-)vector <int> Head will record the key value of every head in this directed graph 

-)vector<Header_Pointer> Header_Node record the pointer to each header 

Function
-)void function string split will juz split the string entered by user and record the result in the vector temp_string.

-)int function Check_Header and void function Check_Activity
  Same as the previous homework.Because vector<Header_Pointer> is used, the index of this vector does not represent the key value of the vertex. For instance , 
  vertex with key value =1 is not stored at Header_Node.at(1).Instead , it's index in the vector is unknown. Therefore,function check_Header is used to check the 
  existence of the header in the vector and return it's index if it exist . If not , return the size of the vector Header_node. The only difference between these 
  two function is that function Check_Header will return it's found index while Check_Acticity will check the temp_Activity(which is a Activity_Pointer) directly.

-)void Update_Count.All the key value of head is recorded in the vector Head.This function will go through this vector can calculate the number of time a specific
  key value appear in the vector.This number will later be the count for the coresponding vertex.Example ,if vertex 4 be head of 3 vertices , int 4 will appear 4
  times in the vector Head and therefore the count is 4.

-)void Topological_Order.This function will find the topological order of this directed graph using the same concept mentiones in the textbook . This result is then
  stored into the vertor head.(Since vector head is useless after determining count, reuse of vector head in this function just to save more space).

Main
-)Same as previous question , when the user start entering the edge , the main function will call Check_Header.If the correcponding header does not exist , it will 
  create a new header for this vertex.If it exist , then it will update the header by adding a new node to it. In the same time, Edge struct is created to record 
  the head and tail of this edge.

-)After this, Node struct will be created and Next from coresponding Header will points toward this struct.The key value of each node struct is the pushback to 
  vector head for the funciton Update_Count function which will be called next.

-)After conforming the number of event , ee[no_event] and le[no_event] is created. Because ee if to find maximum while le is to find minimum, therefore the \
  corresponding initial value for them will be 0 and 1000.

-)Topological_Order function is then called .

-)Accordding to the topological order found ,ee is than calculate according to that order using the same concept as mentioned in the textbook.le will also be 
 determined but in the reverse order of topological order.

-)e[no_Edge],l[no_Edge],slack[no_Edge] is than created.For each activity , e and l is updated by referring to the ee and le forming before. Check_Header and Check_Activity
  function will be used to locate the pointer to corresponding head and tail as recorded in the edge struct .Slack is the minus of e from l.If slack equal to 0 , then this
  activity is critical .