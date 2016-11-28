def bigO_compare(m1,m2,k1,k2):
#Function compares runtime of 2 hypothetical functions O(m1*n+k1) and O(m2*n+k2) and outputs integer 'n' where they intercept
    n = 0
    o1 = m1 * n + k1
    o2 = m2 * n + k2
    
    if m1 == m2:
    #if m1 and m2 are equal, they are parallel and will not intercept
        if k1 == k2:
            #if k1 and k2 are equal, the functions are identical: 0 is output
            return 0
        #if constants are different, the functions will never intercept, return false
        return False 
    
    while True:
        switch = o2 > o1
        o1 = m1 * n + k1
        o2 = m2 * n + k2
        switch2 = o2 > o1
        #functions are tested and compared twice, if comparison changed after functions are updated, functions have intercepted
        if switch != switch2:
            return n
        n+=1
