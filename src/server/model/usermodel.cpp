#include "usermodel.hpp"
#include "db.hpp"
#include<iostream>
using namespace std;

//注册用户时将用户消息插入数据库中
 bool userModel::insert(User &user)
 {
    MySQL mysql;
    char sql[1024];
    sprintf(sql,"insert into user(name,password,state) values('%s','%s','%s')",user.getName().c_str(),user.getPassword().c_str(),user.getState().c_str());
    if(mysql.connect())
    {
        if(mysql.update(sql))
        {
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
 }

//登入是查询数据库检查用户是否正确
 User userModel::query(int id)
 {
     MySQL mysql;
     char  sql[1024]={0}; 
     sprintf(sql,"select * from user where id=%d",id);
     if(mysql.connect())
     {
         MYSQL_RES *res = mysql.query(sql);
         if(res!=nullptr)
         {
             MYSQL_ROW row = mysql_fetch_row(res);
             if(row!=nullptr)
             { 
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPassword(row[2]);
                user.setState(row[3]);

                return user;
             }
         }
     }
     return User();
 }

//更新用户state消息
 bool userModel::updatestate(User user)
 {
     MySQL mysql;
     char  sql[1024]={0}; 
     sprintf(sql,"update user set state='%s' where id=%d",user.getState().c_str(),user.getId());
     if(mysql.connect())
     {
         if(mysql.update(sql))
            {
                user.setId(mysql_insert_id(mysql.getConnection()));
                return true;
            }
     }
     return false;
 }

//重置用户state信息
void userModel::resetState()
{
     MySQL mysql;
     char  sql[1024]="update user set state='offline' where state='online'"; 
     if(mysql.connect())
     {
         mysql.update(sql);
     }
}