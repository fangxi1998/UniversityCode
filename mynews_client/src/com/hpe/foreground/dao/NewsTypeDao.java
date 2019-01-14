package com.hpe.foreground.dao;

import java.sql.SQLException;
import cn.itcast.jdbc.TxQueryRunner;
import java.util.List;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;

import com.hpe.foreground.newsdomain.Count;
import com.hpe.foreground.newsdomain.MinNews;
import com.hpe.foreground.newsdomain.MinNews2;
import com.hpe.foreground.newsdomain.NewsContent;
import com.hpe.foreground.newsdomain.NewsType;






public class NewsTypeDao {
	
	private QueryRunner qr= new TxQueryRunner();
	
	public int count() {
		
		
		 try {
			 String sql= "select count(*) count from t_newstype";
			Count count=  qr.query(sql, new BeanHandler<Count>(Count.class));
			return Integer.parseInt(count.getCount());
		  }catch(SQLException e){
			  throw new RuntimeException();
			  
			  
		  }
	
		
	}
	
	
	
	public List<MinNews> findHot() {
		  try {
			  String sql = "select newsId,title,publishDate,typeId  from t_news ORDER BY click desc limit 8 ";
			  return qr.query(sql, new BeanListHandler<MinNews>(MinNews.class));
		  }catch(SQLException e){
			  throw new RuntimeException();
			  
			  
		  }

		  
		  
}
	
	
	
	public List<MinNews> findNew() {
		  try {
			  String sql = "select newsId,title,publishDate,typeId from t_news  order by publishDate desc limit 8 ";
			  return qr.query(sql, new BeanListHandler<MinNews>(MinNews.class));
		  }catch(SQLException e){
			  throw new RuntimeException();
			  
			  
		  }

}
	
	
	
	
	public List<NewsType> findAll() {
		  try {
			  String sql = "select * from t_newstype";
			  return qr.query(sql, new BeanListHandler<NewsType>(NewsType.class));
		  }catch(SQLException e){
			  throw new RuntimeException();
			  
			  
		  }

}
	
	
	
	public List<MinNews2> findNews(int  typeId){
		
		
		  try {
				 String sql ="select newsId,title,publishDate,typeId,typeName from t_news ne "
				 		+ "INNER JOIN t_newstype ty on ne.TypeId = ty.newsTypeId   "
				 		+ "where typeId =? ORDER BY publishDate DESC LIMIT 5";

			  return qr.query(sql, new BeanListHandler<MinNews2>(MinNews2.class),typeId);
		  }catch(SQLException e){
			  throw new RuntimeException();
			  
			  
		  }
	}
	
	
	
	
	public List<MinNews> findByTypeId(int  typeId) {
		 String sql ="select newsId,title,publishDate,typeId from t_news  where typeId =? ORDER BY publishDate DESC";
		 
		 try {
			return qr.query(sql, new BeanListHandler<MinNews>(MinNews.class),typeId);
		} catch (SQLException e) {
			throw new RuntimeException();
		}
			
		}
	
	
	
	
	
	public NewsContent findByNewsId(int newsId){
 String sql ="select newsId,title,publishDate,typeId,author,content,typeName from t_news n INNER JOIN t_newstype e on n.typeId = e.newsTypeId where newsId=?";
		 
		 try {
			return qr.query(sql, new BeanHandler<NewsContent>(NewsContent.class),newsId);
		} catch (SQLException e) {
			throw new RuntimeException();
		}
		
		
	}
}
