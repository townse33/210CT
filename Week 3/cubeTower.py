def cubeTower(A):
    """Function maximises height of tower B using list of cubes A which consists of tuples representing colour then size"""

    A = sorted(A,reverse=True)
    #A descending list of cube sizes is guaranteed to ensure cubes are not bigger than their predecessor
    B = list()
    B.append(A[0]) #Initiliase output list with first cube
  
    for k in range(len(A)-1):
        
        if A[k] == A[k+1]: 
        #If adjacent cubes are of equal colour, other cubes of same size will be checked
            if k == len(A)-2:
                break #No swapping is possible if item is penultimate in list
            
            maxK = len(A)-k #Used to iterate over remaining cubes
            
            for k2 in range(2,maxK):
            #Start from 2 as adjacent element is of same colour
                
                if A[k+k2][0] != A[k][0]:
                #If the sizes are unequal, swapping is not possible
                    break
                
                if A[k][1] != A[k+k2][1]:
                #If the cubes are of different colours, swap with next element to maximise tower height
                    temp = A[k+1]
                    A[k+1] = A[k+k2]
                    A[k+k2] = temp
                    break
            
        if A[k][1] != A[k+1][1]:
            B.append(A[k+1]) #If conditions are satisfied, the cube can be safely added to the list
        
    return B

#Example method, outputs [(3,B),(2,R),(2,G),(2,R),(1,B)], taking into account optimisation with same-sized cubes

cubes = [(1,"B"),(2,"R"),(2,"R"),(2,"G"),(3,"B")]

print(cubeTower(cubes))
