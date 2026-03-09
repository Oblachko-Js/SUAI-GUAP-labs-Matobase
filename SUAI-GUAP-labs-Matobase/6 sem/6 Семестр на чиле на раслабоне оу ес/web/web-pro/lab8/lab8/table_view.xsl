<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
  <html>
  <head>
    <title>Каталог роботов-игрушек (табличное представление)</title>
    <style>
      table {
        border-collapse: collapse;
        width: 100%;
        margin: 20px 0;
      }
      th, td {
        border: 1px solid #ddd;
        padding: 8px;
        text-align: left;
      }
      th {
        background-color: #f2f2f2;
      }
      img {
        max-width: 100px;
        max-height: 100px;
      }
      .highlight {
        background-color: #ffffcc;
      }
    </style>
  </head>
  <body>
    <h2>Каталог роботов-игрушек</h2>
    <table>
      <tr>
        <th>Изображение</th>
        <th>Название</th>
        <th>Производитель</th>
        <th>Цена</th>
        <th>Возраст</th>
        <th>Вес</th>
        <th>Рейтинг</th>
      </tr>
      <xsl:for-each select="catalog/robot">
      <xsl:sort select="rating" order="descending"/>
      <tr>
        <xsl:if test="rating &gt; 4.5">
          <xsl:attribute name="class">highlight</xsl:attribute>
        </xsl:if>
        <td><img src="{image}" alt="{name}"/></td>
        <td><xsl:value-of select="name"/></td>
        <td><xsl:value-of select="manufacturer"/></td>
        <td><xsl:value-of select="price"/> <xsl:value-of select="price/@currency"/></td>
        <td><xsl:value-of select="age_range"/></td>
        <td><xsl:value-of select="weight"/></td>
        <td><xsl:value-of select="rating"/>/5</td>
      </tr>
      </xsl:for-each>
    </table>
  </body>
  </html>
</xsl:template>
</xsl:stylesheet>