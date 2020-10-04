#include"friendmodel.hpp"
#include"db.hpp"

 //添加用户模块
void FriendModel::insert(int userid,int friendid)
{   
    char sql[1024]={0};
    sprintf(sql,"insert into friend values(%d,%d)",userid,friendid);
    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql);
    }
}

//返回用户好友信息
vector<User> FriendModel::query(int userid)
{
    char sql[1024]={0};
    sprintf(sql,"select a.id,a.name,a.state from user a inner join friend b on a.id=b.friendid where userid=%d ",userid);
    MySQL mysql;
    vector<User> user_vec;
    if(mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);
        if(res!=nullptr)
        {
            MYSQL_ROW row;
            while (row = mysql_fetch_row(res))
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                user_vec.push_back(user);
            }
            mysql_free_result(res);
            return user_vec;
        }
    }
    return user_vec;
}