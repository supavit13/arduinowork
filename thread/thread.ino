#include <Thread.h>
#include <ThreadController.h>

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//My Thread (as a pointer)
Thread* myThread = new Thread();
//His Thread (not pointer)
Thread hisThread = Thread();

// callback for myThread
void niceCallback(){
  Serial.print("A");
  delayMicroseconds(100);
  Serial.print(millis());
  delayMicroseconds(100);
}

// callback for hisThread
void boringCallback(){
  Serial.print("B");
  delayMicroseconds(100);
  Serial.print(millis());
  delayMicroseconds(100);
}

void setup(){
  Serial.begin(9600);

  // Configure myThread
  myThread->onRun(niceCallback);
  myThread->setInterval(0);

  // Configure myThread
  hisThread.onRun(boringCallback);
  hisThread.setInterval(0);

  // Adds both threads to the controller
  controll.add(myThread);
  controll.add(&hisThread); // & to pass the pointer to it
}

void loop(){
  // run ThreadController
  // this will check every thread inside ThreadController,
  // if it should run. If yes, he will run it;
  controll.run();

  // Rest of code
  Serial.println();
}
