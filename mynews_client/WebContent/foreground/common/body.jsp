<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
	<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>


<c:forEach var="x" begin="1" end="${count}">
<c:if test="${(x+2)%3==0}">
<div class="row-fluid">

</c:if>

<div class="span4">
			<div class="data_list news_list">
						<div class="dataHeader">
						${type.get(x-1).typeName}
							
							<span class="more">
								<a href="<c:url value='/NewsServlet?method=show&typeId=${type.get(x-1).newsTypeId}'/>">更多...</a>
							</span>
						</div>
						<div class="datas" >
							<ul>
							 <c:forEach items ="${new1.get(x)}" var ="newstitle" >
							
							 
							 <li>
								<%-- ${newstitle.publishDate}&nbsp; --%>
								<a href="<c:url value='/NewsServlet?method=show1&newsId=${newstitle.newsId}'/>">
									${newstitle.title}
								</a>
							</li>
							
							

	

</c:forEach>
				
							
							</ul>
						</div>
				</div>
	
				
			</div>
			<c:if test="${x%3==0}">
</div>

</c:if>
		
			</c:forEach>
		
		
	
		
		
		
			

</body>
</html>