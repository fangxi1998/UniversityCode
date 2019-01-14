package com.hpe.background.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.hpe.background.domain.User;
import com.hpe.background.service.UserException;
import com.hpe.background.service.UserService;

import cn.itcast.commons.CommonUtils;
import cn.itcast.servlet.BaseServlet;

/**
 * Servlet implementation class UserServlet
 */
@WebServlet("/UserServlet")
public class UserServlet extends BaseServlet {
	private static final long serialVersionUID = 1L;
	private UserService userService = new UserService();
	public String quit(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
	
	request.getSession().invalidate();
	return "r:/background/login.jsp";
	}
	
	public String login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
	
		
		User form = new User();
		form.setUserName(request.getParameter("userName"));
		form.setPassword(request.getParameter("password"));
		System.out.println(form.getPassword());
		System.out.println(form.getUserName());
		
		
		try {
			User user = userService.login(form);
			request.getSession().setAttribute("session_user", user);
			
			return "r:/background/main.jsp";
			
			
		}catch(UserException e){
			request.setAttribute("mes", e.getMessage());
			request.setAttribute("form", form);
			return "f:/background/login.jsp";
		}
		
		
	
	}
	
	
	

}
