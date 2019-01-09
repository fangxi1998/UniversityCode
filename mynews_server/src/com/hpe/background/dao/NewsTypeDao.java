package com.hpe.background.dao;

import java.sql.SQLException;
import cn.itcast.jdbc.TxQueryRunner;
import java.util.List;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;

import com.hpe.background.domain.NewsContent;
import com.hpe.background.domain.NewsType;








public class NewsTypeDao {
	
	private QueryRunner qr= new TxQueryRunner();
	
	
	
	
	

	
	

	
	
	
	
	public List<NewsType> findAll() {
		  try {
			  String sql = "select * from t_newstype";
			  return qr.query(sql, new BeanListHandler<NewsType>(NewsType.class));
		  }catch(SQLException e){
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
