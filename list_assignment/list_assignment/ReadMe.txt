Exam Assignment ReadMe

Name:
Student ID:

ToDo: Record your answers to questions 1 and 2 here. Code should be written in list_assignment.cpp

Question 1:
    code:

    std::list<int> l = { 1,2,3,4 };
    std::list<int> l2 = l;
    cout << "List 1 address: " << &l << endl;
    cout << "List 2 address: " << &l2 << endl;
    auto it1 = l.begin();
    auto it2 = l2.begin();
    cout << "Location of member from list 1: " << &it1 << endl << "Value: " << *it1 << endl;
    cout << "Location of member from list 2: " << &it2 << endl << "Value: " << *it2 << endl;

    output: 

    List 1 address: 0000005AC4F1F528
    List 2 address: 0000005AC4F1F558
    Location of member from list 1: 0000005AC4F1F588
    Value: 1
    Location of member from list 2: 0000005AC4F1F5B8
    Value: 1

    This experiement shows the location of the list and the copied list, as well as their members. If the locations are the same, that means that the copied list points to the same list, so it's a shallow copy
    If the locations are different, new memory was allocated and the list and each member was copied and stored at a new location, so it's a deep copy

    shallow or deep?

    std::list provides a deep copy constructor as new memory is allocated for the copied list and its members


Question 2:

    iterator type:

    my_list_iterator defines a bidirectional iterator, as it can move forwards (++) and backwards (--) on a list

    code (true):

        my_list* list = new my_list();
        list->push_back(1);
        list->push_back(2);
        list->push_back(3);
        list->push_back(3);
        list->push_back(5);

        bool isSorted = std::is_sorted(list->begin(), list->end());
        cout << "Sorted: " << std::boolalpha << isSorted << endl;

    output:
    
        Sorted: true

    code (false):

        my_list* list = new my_list();
        list->push_back(1);
        list->push_back(2);
        list->push_back(3);
        list->push_back(6);
        list->push_back(5);

        bool isSorted = std::is_sorted(list->begin(), list->end());
        cout << "Sorted: " << std::boolalpha << isSorted << endl;

    output:

        Sorted: false

    std::sort work?

        No, because the iterator is not random access, and std::sort needs a random access iterator that can access any member at constant time