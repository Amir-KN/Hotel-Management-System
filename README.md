# Hotel-Management-System

## Architecture
We use **socket.h** library for create a *client server* connection. We use `select()` systemcall to handle requests from multiple clients without blocking the server process.\
The `port` for *server* & *client* and `ip` for *client* read from `config.json` file. Also the list of Users and Rooms and their details read from `UsersInfo.json` & `RoomsInfo.json` files and store in server([Describe in Structure part](#Structure)). We create an `Errors.json` file to write all errors and message that show in client.

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
- After that you should run the **Server** as `s.out` and **Client** as `c.out` in diffrent terminal page :
```
$ ./s.out
```

```
$ ./c.out
```

## Menu of Users
Each user can choose below options :
  - [`View User Information`](#View-User-Information)
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
This option print the user information without password.

### View All Users
We handle this option with below function in Server :
```c++
void Server::HandleViewAllUser(int client_fd);
```
Only admins can use this option. By select this option, admin see the information of all users. 

### View Rooms Informations
We handle this option with below function in Server :
```c++
void Server::HandleViewRoomInfo(int client_fd);
```
This option print the information of each room. All users can use this option.

### Booking
We handle this option with below function in Server :
```c++
void Server::HandleBooking(int client_fd);
```
Only normal users can use this option. With help of this option normal users can book a room if the room has enough beds.

### Canceling
We handle this option with below function in Server :
```c++
void Server::HandleCanceling(int client_fd);
```
Normal user can cancel their reservations. At first we print all reserve of user and the he/she can cancell each reservation.

### Pass Day
We handle this option with below function in Server :
```c++
void Server::HandlePassDay(int client_fd);
```
Only admins can use this option. With help of this option we can pass day and update the date of system.

### Edit Information
We handle this option with below function in Server :
```c++
void Server::HandleEditInfo(int client_fd);
```
Both admins and normal users can edit information with help of this option.
Admins can change the password and normal user can change password, phone and address.

### Leaving Room


### Rooms
We handle this option with below function in Server :
```c++
void Server::HandleRooms(int client_fd);
```
With help of this option, admins can ADD, REMOVE and MODIFY the rooms.

### Logout
We handle this option with below function in Server :
```c++
void Server::HandleExit(int client_fd);
```
If a user select this option, he/she logout from account and the client close.

When we close the server, json files update with `Data.UpdateData();`.