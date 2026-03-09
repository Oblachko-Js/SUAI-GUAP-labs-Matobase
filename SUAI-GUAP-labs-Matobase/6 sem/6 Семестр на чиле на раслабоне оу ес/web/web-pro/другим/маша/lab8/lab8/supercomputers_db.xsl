<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/">
    <html>
      <head>
        <title>Каталог суперкомпьютеров из базы данных</title>
        <style>
          table { border-collapse: collapse; width: 100%; }
          th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
          th { background-color: #f2f2f2; }
          .expensive { background-color: #ffebee; }
        </style>
      </head>
      <body>
        <h2>Суперкомпьютеры (данные из БД)</h2>
        <table>
          <tr>
            <th>ID</th>
            <th>Название</th>
            <th>Производитель</th>
            <th>Цена</th>
            <th>Год выпуска</th>
            <th>Описание</th>
            <th>Особенности</th>
          </tr>
          <xsl:for-each select="SupercomputersCatalog/supercomputer">
            <xsl:sort select="price" order="descending"/>
            <tr>
              <xsl:if test="price > 700000000">
                <xsl:attribute name="class">expensive</xsl:attribute>
              </xsl:if>
              <td><xsl:value-of select="@id"/></td>
              <td><xsl:value-of select="name"/></td>
              <td><xsl:value-of select="manufacturer"/></td>
              <td><xsl:value-of select="price"/> <xsl:value-of select="price/@currency"/></td>
              <td><xsl:value-of select="@release_year"/></td>
              <td><xsl:value-of select="description"/></td>
              <td>
                <ul>
                  <xsl:for-each select="features/feature">
                    <li><strong><xsl:value-of select="feature_name"/>:</strong> <xsl:value-of select="feature_value"/></li>
                  </xsl:for-each>
                </ul>
              </td>
            </tr>
          </xsl:for-each>
        </table>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>