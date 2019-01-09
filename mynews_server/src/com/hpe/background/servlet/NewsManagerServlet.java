package com.hpe.background.servlet;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.hpe.background.domain.News;
import com.hpe.background.domain.NewsType;
import com.hpe.background.service.NewsTypeService;
import com.hpe.background.service.UserException;
import com.hpe.background.service.UserService;



import cn.itcast.servlet.BaseServlet;

/**
 * Servlet implementation class NewsManagerServlet
 */
@WebServlet("/NewsManagerServlet")
public class NewsManagerServlet extends BaseServlet {
	private static final long serialVersionUID = 1L;
	private UserService userService = new UserService();
	private NewsTypeService newsTypeService = new NewsTypeService();
	
	
	public String  UpdateNews(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException{

		News news = new News();
		news.setNewsId(Integer.parseInt(request.getParameter("newsId")));
		news.setTitle(request.getParameter("title"));
		
		news.setContent(request.getParameter("content"));
		news.setTypeId(request.getParameter("typeId"));
		//System.out.println(news.getTypeId());
		news.setPublishDate(new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()));
		news.setAuthor(request.getParameter("author"));
		String isHead = request.getParameter("isHead");
		if(isHead==null) isHead="0";
		else isHead="1";
		news.setIsHead(isHead);
		String isHot = request.getParameter("isHot");
		if(isHot==null) isHot="0";
		else isHot="1";
		news.setIsHot(isHot);
		//news.setClick("0");
		//news.setIsImage("0");
		//news.setImageName(null);
		System.out.println("头条"+news.getIsHead());
		System.out.println("热点"+news.getIsHot());
		try {
			userService.UpdateNews(news);
		} catch (UserException e) {
			request.setAttribute("mes", e.getMessage());
			request.setAttribute("news", news);
			request.setAttribute("type",userService.findnewsType(news.getTypeId()));
			return "f:/background/news/newsUpdate.jsp";
		}
		
		
		
request.setAttribute("NewsList",userService.findNews());
		
		return "f:/background/news/newsList.jsp";
		
		
		
	}
	public String  modifiy(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException{
		NewsType newsType = new NewsType();
		newsType.setNewsTypeId(Integer.parseInt(request.getParameter("newsTypeId")));
		newsType.setTypeName(request.getParameter("typeName"));
		userService.UpdateNewsType(newsType);
		request.setAttribute("type",newsTypeService.findAll());
		
		
		return "f:/background/newsType/newsTypeList.jsp";
		
		
		
	}
	
	public String  premodifiy(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException{
		NewsType newsType = new NewsType();
		newsType.setNewsTypeId(Integer.parseInt(request.getParameter("NewsTypeId")));
		newsType.setTypeName(request.getParameter("TypeName"));
		request.setAttribute("pretype",newsType);
		
		
		return "f:/background/newsType/newsTypeUpdate.jsp";
		
		
		
	}
	public String  DeleteNews(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException{
		userService.DeleteNewsByNewsId(Integer.parseInt(request.getParameter("NewsId")));
		request.setAttribute("NewsList",userService.findNews());
		
		return "f:/background/news/newsList.jsp";
		
		
		
	}
	
	public String  DeleteNewsType(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException{
		try {
			userService.DeleteNewsTypeByNewsId(Integer.parseInt(request.getParameter("NewsTypeId")));
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UserException e) {
			request.setAttribute("mes", e.getMessage());
			request.setAttribute("type",newsTypeService.findAll());
			
			return "f:/background/newsType/newsTypeList.jsp";
			
		}
		request.setAttribute("type",newsTypeService.findAll());
		
		return "f:/background/newsType/newsTypeList.jsp";
		
		
		
	}
	
	
public String  preNews(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		
		request.setAttribute("type",userService.findnewsType(request.getParameter("typeId")));
		request.setAttribute("news", newsTypeService.findNewsByNewsId(Integer.parseInt(request.getParameter("NewsId"))));
		
		
		
	
		
		return "f:/background/news/newsUpdate.jsp";
		
		
	}
	
public String  NewsList(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		
		request.setAttribute("NewsList",userService.findNews());
		
		
		return "f:/background/news/newsList.jsp";
		
		
	}
	
	
	public String  NewsTypeList(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		
		request.setAttribute("type",newsTypeService.findAll());
		
		
		return "f:/background/newsType/newsTypeList.jsp";
		
		
	}
	
	
	public void AllType(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		
		request.setAttribute("type",newsTypeService.findAll());
		
		
		request.getRequestDispatcher("/background/news/select.jsp").include(request, response);
		
		
	}
	
	public String newsTypeSave(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
		try {
			userService.NewsTypeAdd(request.getParameter("typeName"));
		} catch (UserException e) {
			request.setAttribute("mes", e.getMessage());
			
			return "f:/background/newsType/newsTypeSave.jsp";
		}
		
		
		return "r:/background/default.jsp";
		
		
	}
public String newsSave(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
	
	
	
	News news = new News();
	news.setTitle(request.getParameter("title"));
	
	news.setContent(request.getParameter("content"));
	news.setTypeId(request.getParameter("typeId"));
	System.out.println(news.getTypeId());
	news.setPublishDate(new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()));
	news.setAuthor(request.getParameter("author"));
	String isHead = request.getParameter("isHead");
	if(isHead==null) isHead="0";
	else isHead="1";
	news.setIsHead(isHead);
	String isHot = request.getParameter("isHot");
	if(isHot==null) isHot="0";
	else isHot="1";
	news.setIsHot(isHot);
	news.setClick("0");
	news.setIsImage("0");
	news.setImageName(null);
	System.out.println("头条"+news.getIsHead());
	System.out.println("热点"+news.getIsHot());
	try {
		userService.NewsAdd(news);
	} catch (UserException e) {
		request.setAttribute("mes", e.getMessage());
		request.setAttribute("news", news);
		return "f:/background/news/newsSave.jsp";
	}
	
	return "r:/background/default.jsp";
		
	
	}
	

}
