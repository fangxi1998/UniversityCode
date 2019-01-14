<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>
<!DOCTYPE html >
<html>
<head>
<base href="<%= basePath%>">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link href="style/news.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap-responsive.css" rel="stylesheet">
<script src="bootstrap/js/jQuery.js"></script>
<script src="bootstrap/js/bootstrap.js"></script>
<script type="text/javascript">



function p_del() { 
var msg = "您真的确定要删除吗？\n\n请确认！"; 
if (confirm(msg)==true){ 
return true; 
}else{ 
return false; 
} 
} 

</script>
</head>
<body>
<h5 align="center"><span style="color:red;font-weight:900">${mes}</span></h5>
<div class="data_list backMain">
	<div class="data_content">
		<table class="table table-hover table-bordered">
			<tr>
				
				<th>新闻类别编号</th>
				<th>新闻类别名称</th>
				<th>操作</th>
			</tr>
			
				<c:forEach items="${type}" var="type">
				<tr>
				
					<td>${type.newsTypeId}</td>
					<td>${type.typeName}</td>
					<td>
						<a href='<c:url value ='/NewsManagerServlet?method=premodifiy&NewsTypeId=${type.newsTypeId}&TypeName=${type.typeName}'/>' >
						<button class="btn btn-info" type="button">修改</button></a>
						<a href='<c:url value ='/NewsManagerServlet?method=DeleteNewsType&NewsTypeId=${type.newsTypeId}'/>'  
						onclick="javascript:return p_del()"><button class="btn btn-danger" type="button">
						删除</button></a>
					</td>
				</tr>
				</c:forEach>
				
				
				
			
			
		</table>
	</div>
</div>
</body>
</html>