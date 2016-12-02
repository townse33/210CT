class Tree: #Standard tree structure
    def __init__(self,value,children=list()):
        self.value = value
        self.children = children.copy() #Tree children list must be copied to prevent list aliasing
        
    def preOrder(self):
        print(self.value) #Pre Order: Root printed, then each subtree in sequence
        for child in self.children:
            child.postOrder()

    def postOrder(self):
        for child in self.children: #Post Order: Each subtree printed in sequence, then root
            child.postOrder()
        print(self.value)


class Graph: #Weighted graph class
    def __init__(self,adjList = {}):
        self.adjList = adjList #Adjacency list is dictionary of lists
        
    def addVertex(self,v):
        self.adjList[v] = [] #All vertices are initialised with an empty adjacency list

    def addEdge(self,A,B,weight):
        self.adjList[A].append((B,weight)) #As shown in previous week, vertices must be adjacent to each other to create an undirected edge between them
        self.adjList[B].append((A,weight)) #Adjacenct vertices now are represented by tuples in the format (vertex,weight)

    def addTreeEdge(self,A,B):
        self.adjList[A].append(B) #Used for directional edges required for trees
        
    def maxTree(self,root):
    #Adapted version of Prim's algorithm to create a maximum cost spanning tree, runtime O(n^2)
        
        tempG = Graph() #Temporary graph to form our tree

        for vertex in self.adjList:
            tempG.addVertex(vertex) #Get adjacdency dictionary keys as a list
            
        tempAL = self.adjList.copy() #Copy adjacency list to avoid editing the original list

        maxV = max(tempAL[root],key=lambda v:v[1]) #Same routine as below, but to initialise the graph with the tree root

        tempG.addTreeEdge(root,maxV[0]) 

        tempAL[root].remove(maxV) 

        tempAL[maxV[0]].remove((root,maxV[1]))
      
        for vertex in tempAL:

            if len(tempAL[vertex]) == 0 or vertex == root: #Vertices with no possible further connections are skipped
                continue

            maxV = max(tempAL[vertex],key=lambda v:v[1]) #Lambda is used to get the maximum weighted edge by retrieving second element of vertex tuple

            tempG.addTreeEdge(vertex,maxV[0]) #We form an edge of maximum weight as found earlier between the two vertices: this ensures the cost is maximal

            tempAL[vertex].remove(maxV) #Remove references to each node in their temporary adjacency lists to prevent algorithm getting stuck on that edge
            tempAL[maxV[0]].remove((vertex,maxV[1]))

        treeDict = dict() #We will use a dictionary to create tree nodes at runtime
        for vertex in tempG.adjList:
            treeDict[vertex] = Tree(vertex) #Create a node for each vertex
            
        for vertex in treeDict:
            for adj in tempG.adjList[vertex]:
                treeDict[vertex].children.append(treeDict[adj]) #For each node, add each subsequent adjacent node as a child

        return treeDict[root] #The root is returned so that the tree can be fully retrieved


#Example usage
       
adjList = {1:[(2,1),(3,6)],2:[(1,1),(3,1),(4,8)],3:[(1,6),(2,1)],4:[(2,8)]} #Adjacency list in format {Vertex:(Adjacent Vertex, Edge Weight)}

G = Graph(adjList) 

T = G.maxTree(1) #Each required process for the question 

print("Pre Order: ")
T.preOrder() 
print("Post Order: ")
T.postOrder()
