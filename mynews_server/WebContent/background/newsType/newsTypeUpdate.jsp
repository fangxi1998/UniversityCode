<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>  
  <%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html >
<html>
<head>
<base href="<%=basePath%>">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link href="style/news.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap-responsive.css" rel="stylesheet">
<script src="bootstrap/js/jQuery.js"></script>
<script src="bootstrap/js/bootstrap.js"></script>
<title>新闻网站后台管理</title>
<script type="text/javascript">
	
</script>
</head>
<body>
<h5 align="center"><span style="color:red;font-weight:900">${mes}</span></h5>
<div class="data_list backMain">
	<div class="data_content">
		 <form id="formNewsType" action="<c:url value='/NewsManagerServlet'/>" method="post">
		 <input type="hidden" name="method" value="modifiy"/>
		 
			<table style="padding: 5px">
				<tr>
					<td>
						<label>将${pretype.typeName}修改为：</label>
						
					</td>
					<td>
						<input type="text" id="typeName" name="typeName" value="${pretype.typeName}"/>
					</td>
				</tr>
				<tr>
					<td>
						<input type="hidden" id="newsTypeId" name="newsTypeId" value="${pretype.newsTypeId}"/>
					</td>
					<td>
						<input type="submit" id="btnSubmit" class="btn btn-primary"  value="修改新闻类别"/>&nbsp;&nbsp;
						<input type="button" class="btn btn-primary" value="返回" onclick="javascript:history.back()"/>&nbsp;&nbsp;<font id="error" color="red"></font>
					</td>
				</tr>
				
			</table>
		</form>
	</div>
</div>
</body>
</html>