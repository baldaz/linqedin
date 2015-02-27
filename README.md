Linqedin
========

P2 Project 2014

####Design pattern
    - User -> polymorphic base
        - Account
            - UserInfo
            - UserName

    - LinQNet -> contacts network
        use map / vector / list

    - lib QT 4.8 or 5.3
    - clone methods probably useless
    - remove smartptr.cpp from .pro generated file
    - deep find vs deep copy smartptr    <<<<<<<<<<< --------------------------
####TODO
    - Loader class <<<<< --- object factory, RTTI sensible reduction
    - UserInterface polymorphic hierarchy <<<<< --- RTTI sensible reduction
    - Informations polymorphic hierarchy optimization
    - Comments..
    - DB polymorphic hierarchy [optional]

####Graphic
    - Modularize parts (showuser etc..)

####Exception handling
    - No payments inserted, admin insert

####IMPORTANT
    - Watch for random segfaults in registration with more client logged.
    - 54 seconds compile time
    - save in all critical points