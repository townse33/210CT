def quickSort(L):
    """Standard quick sort algorithm"""
    
    if len(L) == 1:
        return [L[0]] #Return lists of one element as these are sorted
    if len(L) == 0:
        return [] #If no list is to be sorted, an empty list can represent this
    
    pivot = L[0] #We will use the first element in L as our pivot for simplicity
    sublistL = list()
    sublistR = list()

    del L[0] #The pivot is no longer required, so delete this to prevent duplication
    
    for element in L:
        if element < pivot:
            sublistL.append(element)
        else:
            sublistR.append(element)

    return quickSort(sublistL) + [pivot] + quickSort(sublistR) #Concatenating in order produces full list
            
def quickSortM(L,m):
    """Wrapper function to get mth element in ascending order from the quick sort algorithm"""
    return quickSort(L)[m-1]

#Example data, in this case 3 is printed
L = [7,6,6,3,2]

print(quickSortM(L,2))
