package io.swagger.model;

import java.util.Objects;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonCreator;
import io.swagger.v3.oas.annotations.media.Schema;
import org.springframework.validation.annotation.Validated;
import javax.validation.Valid;
import javax.validation.constraints.*;

/**
 * Lesson
 */
@Validated
@javax.annotation.Generated(value = "io.swagger.codegen.v3.generators.java.SpringCodegen", date = "2023-09-13T19:36:10.460669586Z[GMT]")


public class Lesson   {
  @JsonProperty("id")
  private Integer id = null;

  @JsonProperty("num_group")
  private String numGroup = null;

  @JsonProperty("audience")
  private String audience = null;

  @JsonProperty("teacher")
  private String teacher = null;

  @JsonProperty("name")
  private String name = null;

  @JsonProperty("number")
  private Integer number = null;

  public Lesson id(Integer id) {
    this.id = id;
    return this;
  }

  /**
   * Get id
   * @return id
   **/
  @Schema(example = "0", description = "")
  
    public Integer getId() {
    return id;
  }

  public void setId(Integer id) {
    this.id = id;
  }

  public Lesson numGroup(String numGroup) {
    this.numGroup = numGroup;
    return this;
  }

  /**
   * Get numGroup
   * @return numGroup
   **/
  @Schema(example = "4132", required = true, description = "")
      @NotNull

    public String getNumGroup() {
    return numGroup;
  }

  public void setNumGroup(String numGroup) {
    this.numGroup = numGroup;
  }

  public Lesson audience(String audience) {
    this.audience = audience;
    return this;
  }

  /**
   * Get audience
   * @return audience
   **/
  @Schema(example = "23-09", required = true, description = "")
      @NotNull

    public String getAudience() {
    return audience;
  }

  public void setAudience(String audience) {
    this.audience = audience;
  }

  public Lesson teacher(String teacher) {
    this.teacher = teacher;
    return this;
  }

  /**
   * Get teacher
   * @return teacher
   **/
  @Schema(example = "Ivanov", required = true, description = "")
      @NotNull

    public String getTeacher() {
    return teacher;
  }

  public void setTeacher(String teacher) {
    this.teacher = teacher;
  }

  public Lesson name(String name) {
    this.name = name;
    return this;
  }

  /**
   * Get name
   * @return name
   **/
  @Schema(example = "Physics", required = true, description = "")
      @NotNull

    public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public Lesson number(Integer number) {
    this.number = number;
    return this;
  }

  /**
   * Get number
   * @return number
   **/
  @Schema(example = "5", required = true, description = "")
      @NotNull

    public Integer getNumber() {
    return number;
  }

  public void setNumber(Integer number) {
    this.number = number;
  }


  @Override
  public boolean equals(java.lang.Object o) {
    if (this == o) {
      return true;
    }
    if (o == null || getClass() != o.getClass()) {
      return false;
    }
    Lesson lesson = (Lesson) o;
    return Objects.equals(this.id, lesson.id) &&
        Objects.equals(this.numGroup, lesson.numGroup) &&
        Objects.equals(this.audience, lesson.audience) &&
        Objects.equals(this.teacher, lesson.teacher) &&
        Objects.equals(this.name, lesson.name) &&
        Objects.equals(this.number, lesson.number);
  }

  @Override
  public int hashCode() {
    return Objects.hash(id, numGroup, audience, teacher, name, number);
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("class Lesson {\n");
    
    sb.append("    id: ").append(toIndentedString(id)).append("\n");
    sb.append("    numGroup: ").append(toIndentedString(numGroup)).append("\n");
    sb.append("    audience: ").append(toIndentedString(audience)).append("\n");
    sb.append("    teacher: ").append(toIndentedString(teacher)).append("\n");
    sb.append("    name: ").append(toIndentedString(name)).append("\n");
    sb.append("    number: ").append(toIndentedString(number)).append("\n");
    sb.append("}");
    return sb.toString();
  }

  /**
   * Convert the given object to string with each line indented by 4 spaces
   * (except the first line).
   */
  private String toIndentedString(java.lang.Object o) {
    if (o == null) {
      return "null";
    }
    return o.toString().replace("\n", "\n    ");
  }
}
