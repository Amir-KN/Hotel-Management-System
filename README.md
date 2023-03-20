# Hotel-Management-System

## Architecture
We use **socket.h** library for create a *client server* connection. We use `select()` systemcall to handle requests from multiple clients without blocking the server process.\
The `port` for *server* & *client* and `ip` for *client* read from `config.json` file. Also the list of Users and Rooms and their details read from `UsersInfo.json` & `RoomsInfo.json` files and store in server([Describe in Structure part](#Structure)). We create an `Errors.json` file to write all errors and message thar show in client.

## Structure
We have some main Class :
  - `Server` : This class handle **server** and response to request of clients.
  - `Client` : This class handle **client** and can send and receive message from server.
  - `User` : This class is a Super class and store information of all kine of **users** and has 2 children :
      - `Admin` : This class has methods that work for Admin users.
      - `NormalUser` : This class store the information of normal user and the methods work for normal user. 

  - `Room` : This class store the information of rooms like *number of room* and *capacity* and ...
  - `Jsonhandler` : With help of this class we can read and modify the information of users and rooms from json files.
  - `Date` : Handle the time of system.
  - `Logger` : This class logs action of all users. All logs store in *Logs* folder.


## Run The Project
You can run the projet by below steps :
- First you should compile the codes :
```
$ make
```
- After that you should run the `server` and `client` in diffrent terminal page :
```
$ ./s.out
```

```
$ ./c.out
```

## Menu of Users
Each user can choose below options :
  - [View User Information](#View-User-Information)
  - [`View All Users`](#View-All-Users)
  - [`View Rooms Informations`](#View-Rooms-Informations)
  - [`Booking`](#Booking)
  - [`Canceling`](#Canceling)
  - [`Pass Day`](#Pass-Day)
  - [`Edit Information`](#Edit-Information)
  - [`Leaving Room`](#Leaving-Room)
  - [`Rooms`](#Room)
  - [`Logout`](#Logout)
 
 We handle each option with function. Usually at first we call `User->IsAdmin()` method to understand that this user(client) is admin or no and after that 
 we implement action that must be done.

### View User Information
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```

### View All Users
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```

### View Rooms Informations
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```

### Booking
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```

### Canceling
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```

### Pass Day
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```

### Edit Information
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```

### Rooms
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```

### Logout
We handle this option with below function in Server :
```c++
 void Server::HandleViewUserInfo(int client_fd);
```
