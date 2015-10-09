'''
# =============================================================================
#      FileName: Binary_search_recursive.py
#          Desc: Recursive Binary Search
#        Author: Max Lee
#         Email: hoso1312@gmail.com
#      HomePage: http://imnotbermuda.com
#       Version: 0.0.1
# =============================================================================
'''
def bsearch(lst, key, idx=0):
    if lst:
        mid = len(lst)//2

        if lst[mid] == key:
            return (mid+idx)
        if lst[mid] < key:
            return bsearch(lst[mid+1:], key, mid+idx+1)
        return bsearch(lst[:mid], key, idx)

    return False
