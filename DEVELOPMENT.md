# Development

---
 - **4/27/20** Began setting up project
    - Created Point and Segment classes to represent the board
    - Explored how to best incorporate Firebase
        - C++ SDK
            - Limited features (designed for testing mobile features)
            - Difficult to install
        - REST API
            - Easy to install
            - Have to create substantial infrastructure to make easy to use

 - **4/28/20** Created basic drawing whiteboard functionality
 
 - **4/29/20** Finalized decision on how to store information
    - MongoDB via mongcxx driver vs Firebase via REST API
    - MongoDB better fit
        - Simplicity to incorporate
        - Good opportunity to learn about NoSQL databases on a deeper level
    - Installed MongoDB and mongocxx on machine and added to project 

 - **4/30/20** Added storage of segments and color picking

 - **5/1/20** Incorporated a login page
 
 - **5/3/20** Added ability to retrieve segments and fixed bugs
    - Segfault errors when adding null segments
    - Awkward drawing experience when drawing as segments wouldn't be rendered until after finished
    
 - **5/5/20** Refactored code and updated documentation
 
 - **5/6/20**
    - Finalize documentation and testing
    - Add ability to change boards more intuitively while in the drawing page via buttons
