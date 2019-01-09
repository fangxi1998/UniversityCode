<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<select id="typeId" name="typeId">
							<option value="0">请选择新闻类别</option>
							<c:forEach items ="${type}" var ="type">
								<option value="${type.newsTypeId}">${type.typeName}</option>
								</c:forEach>
								
						</select>
	
	