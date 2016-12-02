from unweightedGraph import *

def isConnected(G):
    vertexList = list()
    
    for vertex in G.adjList:
        vertexList.append(vertex)
    #Creates a list of vertices to copy
        
    for vertex in G.adjList:
        
        tempList = vertexList.copy() #list is copied to avoid list aliasing
        tempList.remove(vertex) #we don't consider loops in strong connectivity
        
        for adjV in G.adjList[vertex]:
            tempList.remove(adjV)
        #adjacent vertices are removed from list to find remaining vertices
            
        if len(tempList) > 0:
            print("No")
            return
            #if any vertices are remaining, the graph is not strongly connected
    print("Yes")     
    return

#Example data, every node is connected to every other node; is strongly connected, this outputs "Yes"
adjList = {1:[2,3,4],2:[1,3,4],3:[1,2,4],4:[1,2,3]}

G = graph(adjList)

isConnected(G)
