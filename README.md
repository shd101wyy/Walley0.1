Walley Language 
===================

                ____     ______     _____     /-----------\           
                 \\ \    ||    \    ||  |    /-------------\          
                  \\ \   ||  |\ \   ||  |    |  --  |  --  | \\  //   
                   \\ \  ||  |\\ \  ||  |    |   |_____|   |  \\//    
                    \\ \ ||  | \\ \ ||  |  --\_____________/ ---==    
                     \\ \||  |  \\ \||  |  ///\  ||    ||      ||     
                      \\     |   \\     |  |  |  ||    ||      ||     
                       \\____|    \\____|  \__/\ ||___ ||__e   ||     
               __________________________________________________||     
               ---------------------------------------------------|     
                       VERSION 0.1.618  FOR FUTURE AR,VR,AI  
       
                    Walley Language is a script language that       
                    compiles Walley Language into JavaScript which  
                    can be embeded into webpage. Parts of Walley    
                    Language require Node.Js support.                 
                                                                                    
                       It is the language for creating a WORLD:)   


        I just started this project, so there are still lots of bugs.
        XD

        To install walley language,
        type "npm install -g walley-language" in terminal or cmd

        to run walley-language, simply type "walley_worker" in terminal

        ========
        Command:
        walley_worker                 | interactive mode (compile to js and run immediately)
        walley_worker [file]          | run .wy file directly
        walley_worker compile [file]  | compile .wy file and show output in terminal
        walley_worker compile [file1] [file2]
                                      | compile file1 and save the output to file2

        ========
        The walley.wy source file has three parts:
          1. lexer                | get token list
          2. parser               | convert token list to syntax tree
          3. code generation      | compile the code to javascript code using the syntax tree
          4. code optimization    || not started yet

        ========
        Keywords:
            and break then if elif else end 
            true false for def if in local none
            not or return while import

        ========
        Walley Language now support the following data types:
          1. String               | only support "" now. '' is unsupported
          2. Number               | eg 10.0 12
          3. Table                | influenced by lua, [] . it is a wrapper for Object
          4. Function

        ========
        Grammer:  # means the feature is not supported now

          assign value:
            x=12
            x,y=14,15
            a=[]
            a[2]=15

          define function:
            1. def [ func_name ] ( [ params ] ) then [ statements ] end
              eg:
                def add(num1,num2) then return num1+num2 end
            2.  [ var_name ] = def ( [ params ] ) then [ statements ] end
              eg:
                add = def (num1,num2) then return num1+num2 end

          if elif else:
            1. if [ judge ] then [ statements ] end
              eg: if x>10 then x=15 end
            2. if [ judge ] then [ stms ] elif [ judge ] then [ stms ] end
              eg: if x>0 then x=12 elif x<20 then x=1 end
            3. if [ judge ] then [ stms ] (elif [judge] then [stms] ) else [stms] end
              eg: if x<0 then x=14 elif x>20 then x=1 else x=50 end

          while: 
            1. while [ judge ] then [ statements ] end

          for:  (still under development.. I may replace while with for in the future)
            1. for [stm1] , [judge] , [stm2] then [stms] end
            2. for , [judge] , [stm2] then [stms] end
            3. for [judge] , [stm] then [stms] end
            # 4. for [judge] then [stms] end

          foreach:
            1. for [key],[value] in [table] then [stms] end
              eg:
                for i,v in [1,2,3,a=14] then
                  console.log(i)  # print 0,1,2,a
                  console.log(v)  # print 1,2,3,14
                end
            2. for [key] in [table] then [stms] end

          annotation:
            # [stm]      : short annotation
            #~ [stms] ~# : long annotation

          06/07/2013 new add:
          import: ＃ import statement needs nodejs support
            1. import [ file_name (string) ]
              eg: import "Hello.wy"
                    will import all from Hello.wy.. like c language include ""
                    
        ========
        slice:
          only support string and table
          [start:end]
          [:end]
          [start:]
          eg: "Hello"[0:2]--> "He"
              [1,2,3][0:2]--> [0,1]

        ========
        embed library:
          Math: (support all javascript Math prototype functions) new added:  
            Math.cot, Math.sec, Math.csc
          String: (support all javascript String prototype functions) new added:
            find, toupper, tolower, reverse
          Table:  (support all javascript Object prototype functions) new added:
            slice, append, maxn, insert, remove, length
          Builtin:
            len([string|table]), isalpha, isdigit

        ========
        How to define a class using walley language:

          Human=[]                # define a class Human
          Human.init=def()then    # constructor
            self=[]               #
            self.age=12           #  instance public value
            self.showAge=def()then # instance public method
              console.log(self.age)
            end
            x=12                  # private value
            y=def()then           # private method
              console.log("nothing")
            end
            return self
          end
          Human.hi="Hello World"   # class value
          Human.speak=def(msg)then # class method
            console.log(msg)
          end

          # init an object
          yiyi = Human.init()
          yiyi.showAge()          # call instance method "showAge"

          Human.speak("I am human!!") # call class method "speak"

        ========
        Problem: (@ means support now)
          Unsupported features or unsolved problems:
            @1. += -= *= /=     ...
            @2. ++ -- **        ...
            3. x = new Hi()     # new is not supported
            4. ... (argv) in params
            5. switch statements
            6. keyword as var name problem
            7. << >> operator
            8. and a lot....XD
            9. no beautifier
            10. for statement i++ error

            11 inefficient for statements in walley_cg.wy
            12 inefficient way of finding the index of ")" and "then"

        ========
          Released under MIT License

          Github:
              Repository   https://github.com/shd101wyy/Walley0.1.git (git)
              Bugs  https://github.com/shd101wyy/Walley0.1/issues: 

        ========
          version 0.1.616: fix function as function param bug.. fix one lexer bug
          version 0.1.617: fix [1,2,3,4][0:2] bug, i convert {0:1,0:2} to array and then get slice
                           but actually maybe i should convert it back to obj because table is object

          version 0.1.618: fix for each bug, fix slice bug










