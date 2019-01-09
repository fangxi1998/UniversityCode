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
<base href="<%=basePath%>">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link href="style/news.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap.css" rel="stylesheet">
<link href="bootstrap/css/bootstrap-responsive.css" rel="stylesheet">
<script src="bootstrap/js/jQuery.js"></script>
<script src="bootstrap/js/bootstrap.js"></script>
<script type="text/javascript">
	
</script>
</head>
<body>
	<div class="data_list backMain">
		<div class="data_content">
			<table class="table table-hover table-bordered">
				<tr>
					<th>链接编号</th>
					<th>链接名称</th>
					<th>链接地址</th>
					<th>联系人邮件</th>
					<th>操作</th>
				</tr>
				<tr>
					<td>1</td>
					<td>百度</td>
					<td>http://www.baidu.com</td>
					<td>zhangsan@baidu.com</td>
					<td>
						<button class="btn btn-mini btn-info" type="button" onclick="">修改</button>&nbsp;&nbsp;
						<button class="btn btn-mini btn-danger" type="button" onclick="">删除</button>
					</td>
				</tr>
				<tr>
					<td>1</td>
					<td>百度</td>
					<td>http://www.baidu.com</td>
					<td>zhangsan@baidu.com</td>
					<td>
						<button class="btn btn-mini btn-info" type="button" onclick="">修改</button>&nbsp;&nbsp;
						<button class="btn btn-mini btn-danger" type="button" onclick="">删除</button>
					</td>
				</tr>
				<tr>
					<td>1</td>
					<td>百度</td>
					<td>http://www.baidu.com</td>
					<td>zhangsan@baidu.com</td>
					<td>
						<button class="btn btn-mini btn-info" type="button" onclick="">修改</button>&nbsp;&nbsp;
						<button class="btn btn-mini btn-danger" type="button" onclick="">删除</button>
					</td>
				</tr>
			</table>
		</div>
	</div>
</body>
</html>