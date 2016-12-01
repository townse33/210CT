class graph:
#Unweighted graph class
    
    def __init__(self,adjList=dict()):
        self.adjList = adjList
        #Dictionary used to hold adjacency data, keys are vertices, values are list of adjacent vertices
        
    def addVertex(self,vertex):
        self.adjList[vertex] = []
        #Adding a vertex simply consists of initialising its adjacency list in the dictionary
        
    def addEdge(self,A,B):
        self.adjList[A].append(B)
        self.adjList[B].append(A)
        #Adding an edge requires both vertices to be added to each other's adjacency list

    def isPath(self,v,w,prev=[]):
    #Pathfinding function that utilises depth first search to find the vertex

        prev.append(v)

        if v == w:
            file = open("path.txt.",'w')
            file.write(str(prev)) #Writing the nodes visited in this recursion path is equivalent to the path between the vertices
            file.close()
            return

        for vertex in self.adjList[v]:
            if vertex not in prev:
                self.isPath(vertex,w,prev.copy()) #By only visiting unvisited vertices per recursion, backtracking in the same path is avoided
                #Note that the 'prev' list was copied to avoid list aliasing


#Example usage, outputted 1,3,4 to the text file
if __name__ == "__main__":
    adjList = {1:[2,3],2:[1],3:[1,4],4:[3]}

    G = graph(adjList)

    G.isPath(1,4)     
