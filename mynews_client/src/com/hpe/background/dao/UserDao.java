package com.hpe.background.dao;

import java.sql.SQLException;
import java.util.List;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;

import com.hpe.background.domain.Count;
import com.hpe.background.domain.MinNews2;
import com.hpe.background.domain.News;
import com.hpe.background.domain.NewsType;
import com.hpe.background.domain.User;


import cn.itcast.jdbc.TxQueryRunner;

/**
 * Êý¾ÝÀà
 * @author fangxi
 *
 */
public class UserDao {
	private QueryRunner qr = new TxQueryRunner();
	
	public int count( int id) {
		
		
		 try {
			 String sql= "select count(*) count from t_news where typeId = ?";
			Count count=  qr.query(sql, new BeanHandler<Count>(Count.class),id);
			return Integer.parseInt(count.getCount());
		  }catch(SQLException e){
			  throw new RuntimeException();
			  
			  
		  }
	
		
	}
	
	
	
	
	public void UpdateNews(News news) {
		String sql="UPDATE t_news SET title =?,content=?,author =?,typeId = ?,isHead=?,isHot=?"
				+ ",publishDate=? where newsId=?";
		Object[] params = {news.getTitle(),news.getContent(),news.getAuthor(),news.getTypeId(),
						   news.getIsHead(),news.getIsHot(),news.getPublishDate(),news.getNewsId()};
		
		try {
			qr.update(sql, params);
		} catch (SQLException e) {
			throw new RuntimeException();
		}
		
		
	}
	
	public void UpdateNewsType(NewsType newsType) {
	String sql=  "UPDATE t_newstype SET typeName = ? where newsTypeId = ?";
	Object[] params = {newsType.getTypeName(),newsType.getNewsTypeId()};
	
	try {
		qr.update(sql, params);
	} catch (SQLException e) {
		throw new RuntimeException();
		
	}		
		
		
	}
	public void DeleteNewsByNewsId(int newsId) {
		
		
		String sql = "DELETE from t_news where newsId = ?";
		try {
			qr.update(sql, newsId);
		} catch (SQLException e) {
			throw new RuntimeException();
			
		}
		
	}
	public List<NewsType> findnewsType(String id){
		
	String sql = "	SELECT * FROM t_newstype ORDER BY newsTypeId<> ?";
	try {
		return qr.query(sql, new BeanListHandler<NewsType>(NewsType.class), id);
	} catch (SQLException e) {
		throw new RuntimeException();
	}
	
		
		
	}

	public List<MinNews2> findNews(){
		
		
		  try {
				 String sql ="select newsId,title,publishDate,typeId,typeName from t_news ne "
				 		+ "INNER JOIN t_newstype ty on ne.TypeId = ty.newsTypeId   "
				 		+ "ORDER BY publishDate DESC,typeName";
			  return qr.query(sql, new BeanListHandler<MinNews2>(MinNews2.class));
		  }catch(SQLException e){
			  throw new RuntimeException();
			  
			  
		  }
	}
	public User findByUsername(String username) {
		try {
			String sql = "select userName,password from t_user where userName =?";
			return qr.query(sql, new BeanHandler<User>(User.class), username);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}

	}

	

	public void NewsAdd(News news) {
		try {
			String sql = "INSERT INTO `t_news`"
					+ "(title,content,publishDate,author,typeId,click,isHead,isImage,imageName,isHot) "
					+ "values(?,?,?,?,?,?,?,?,?,?)";
			Object[] params = {news.getTitle(),news.getContent(),news.getPublishDate(),news.getAuthor(),news.getTypeId(),
								news.getClick(),news.getIsHead(),news.getIsImage(),news.getImageName(),news.getIsHot()
			
			};
			qr.update(sql, params);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}



	public void NewsTypeAdd(String typeName) {
		String sql = "INSERT INTO `t_newstype`(typeName) VALUES (?)";
		try {
			qr.update(sql,typeName);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
		
	}
	public void DeleteNewsTypeByNewsId(int newsTypeId) {
		String sql = "DELETE from t_newstype where newsTypeId = ?";
		try {
			qr.update(sql, newsTypeId);
		} catch (SQLException e) {
			throw new RuntimeException();
			
		}
		
		
	}
	

	

	
	
}
