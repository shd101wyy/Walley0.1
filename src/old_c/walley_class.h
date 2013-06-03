//
//  walley_class.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//
#include "walley_function.h"

/*
 
 // I GIVE UP THIS PART
 
 a.value
 a.length()
 a.value.length()
 
 
 a.value.length()
 ( ((a)(value)) (func length))
 
                
 where . is found from behind
 
 class_property-> class_property '.' id     // a.length
                | class_property '.' func   // a.length()
                | id
                | string
                | list
                | table
                | table_value
*/

/*
 三、极简主义法
 荷兰程序员Gabor de Mooij提出了一种比Object.create()更好的新方法，他称这种方法为"极简主义法"（minimalist approach）。这也是我推荐的方法。
 3.1 封装
 这种方法不使用this和prototype，代码部署起来非常简单，这大概也是它被叫做"极简主义法"的原因。
 首先，它也是用一个对象模拟"类"。在这个类里面，定义一个构造函数createNew()，用来生成实例。
 　　var Cat = {
 　　　　createNew: function(){
 　　　　　　// some code here
 　　　　}
 　　};
 然后，在createNew()里面，定义一个实例对象，把这个实例对象作为返回值。
 　　var Cat = {
 　　　　createNew: function(){
 　　　　　　var cat = {};
 　　　　　　cat.name = "大毛";
 　　　　　　cat.makeSound = function(){ alert("喵喵喵"); };
 　　　　　　return cat;
 　　　　}
 　　};
 使用的时候，调用createNew()方法，就可以得到实例对象。
 　　var cat1 = Cat.createNew();
 　　cat1.makeSound(); // 喵喵喵
 这种方法的好处是，容易理解，结构清晰优雅，符合传统的"面向对象编程"的构造，因此可以方便地部署下面的特性。
 3.2 继承
 让一个类继承另一个类，实现起来很方便。只要在前者的createNew()方法中，调用后者的createNew()方法即可。
 先定义一个Animal类。
 　　var Animal = {
 　　　　createNew: function(){
 　　　　　　var animal = {};
 　　　　　　animal.sleep = function(){ alert("睡懒觉"); };
 　　　　　　return animal;
 　　　　}
 　　};
 然后，在Cat的createNew()方法中，调用Animal的createNew()方法。
 　　var Cat = {
 　　　　createNew: function(){
 　　　　　　var cat = Animal.createNew();
 　　　　　　cat.name = "大毛";
 　　　　　　cat.makeSound = function(){ alert("喵喵喵"); };
 　　　　　　return cat;
 　　　　}
 　　};
 这样得到的Cat实例，就会同时继承Cat类和Animal类。
 　　var cat1 = Cat.createNew();
 　　cat1.sleep(); // 睡懒觉
 3.3 私有属性和私有方法
 在createNew()方法中，只要不是定义在cat对象上的方法和属性，都是私有的。
 　　var Cat = {
 　　　　createNew: function(){
 　　　　　　var cat = {};
 　　　　　　var sound = "喵喵喵";
 　　　　　　cat.makeSound = function(){ alert(sound); };
 　　　　　　return cat;
 　　　　}
 　　};
 上例的内部变量sound，外部无法读取，只有通过cat的公有方法makeSound()来读取。
 　　var cat1 = Cat.createNew();
 　　alert(cat1.sound); // undefined
 3.4 数据共享
 有时候，我们需要所有实例对象，能够读写同一项内部数据。这个时候，只要把这个内部数据，封装在类对象的里面、createNew()方法的外面即可。
 　　var Cat = {
 　　　　sound : "喵喵喵",
 　　　　createNew: function(){
 　　　　　　var cat = {};
 　　　　　　cat.makeSound = function(){ alert(Cat.sound); };
 　　　　　　cat.changeSound = function(x){ Cat.sound = x; };
 　　　　　　return cat;
 　　　　}
 　　};
 然后，生成两个实例对象：
 　　var cat1 = Cat.createNew();
 　　var cat2 = Cat.createNew();
 　　cat1.makeSound(); // 喵喵喵
 这时，如果有一个实例对象，修改了共享的数据，另一个实例对象也会受到影响。
 　　cat2.changeSound("啦啦啦");
 　　cat1.makeSound(); // 啦啦啦
*/