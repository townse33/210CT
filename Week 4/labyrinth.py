def maze2graph(M):
    """Function creates adjancency list by storing adjacent 1s in the maze as dictionary values"""
    adj = dict()

    for row in range(len(M)):
        for col in range(len(M[0])):
                  
            if M[row][col] == 1:

                #Utilises short circuit if statements to avoid out-of-bounds errors
                #If element exists, is adjacent and is 1, then it will be appended to the list
                tempL = list()
                                
                if row > 0 and M[row-1][col] == 1:
                    tempL.append((row-1,col))
            
                if row < len(M)-1 and M[row+1][col] == 1:
                    tempL.append((row+1,col))

                if col > 0 and M[row][col-1] == 1:
                   tempL.append((row,col-1))

                if col < len(M[0])-1 and M[row][col+1] == 1:
                    tempL.append((row,col+1))

                adj[(row,col)] = tempL
      
    return adj

def graphMazeSolver(G,start,current,shape,prev=[]):

    prev.append(current)
    #We can keep track of every path through the recursion and avoid backtracking by simply passing a 'prev' list

    if current != start:
        #Detect if at maze edge using shape data found in mazeSolver
        if min(current) == 0 or current[0] == shape[0] - 1 or current[1] == shape[1] - 1:
            print(prev)
            #By printing previous traversed vertices, we provide the path to the exit
        
        if len(G[current]) == 1:
            #By keeping the return separate for cases where dead-ends are reached, we don't exclude solutions along the edge
            return
    
    for path in G[current]:
        if path not in prev:
            graphMazeSolver(G,start,path,shape,prev)
            
    #For each path not previously visited, we use this as a candidate path to an exit

    return 

def mazeSolver(M,start):
    """Wrapper function to convert maze to a graph before beginning
       the actual maze solving process"""

    shape = (len(M),len(M[0]))

    graph = maze2graph(M)

    return graphMazeSolver(graph,start,start,shape)
                
#Example use of functions as per question spec: 1s for corridors, 0s for walls
maze = [[0,1,0,0],
        [0,1,1,0],
        [0,0,1,1],
        [0,0,0,1]]

mazeSolver(maze,(0,1))

