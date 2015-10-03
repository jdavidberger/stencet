## About

Stencet is a templating engine made in the vein of liquid template and Django.

It’s goal is to be fast and lightweight, but also easy to use, especially from the designer side. The language itself is meant to be a drop-in replacement for Django’s templating, although many tags and filters still have to be added -- officially the project is in alpha release.

The templating system isn't geared specifically towards any rendered language. You can render HTML, CSS, XML, etc.

## Why not use ______ templating engine?

*   **ctemplate** - CTemplates are useful, however it lacks a proper include/extension system. Having to specify which template file to include, for instance, breaks a pure seperation between the model and the view.*   **grantlee** - Grantlee is great for what it is for, but it has a dependency on Qt which isn't appropriate for a wide variety of projects.

## Features

Current Features:

*   Fast rendering of templates in a language that is widely used
*   Easily customizable (implement two functions!) tags and filters

Planned Features for beta release:

*   Drop-in replacement for Django templates
*   Dynamic loading of filters through shared libraries

## Example

**test.tc**:

```HTML+Django
<html> 
  {% include 'header' %}
  <body>
    <ul>
	{% for item in menu %}
	   <li> {{ item | capfirst }} </li>
	{% endfor %}
    </ul>
  </body>
</html>
```

**header.tc**:

```HTML+Django
<head><title>Menu</title><head>
```

**test.cc**:

```C++
int main() {
  Variant vm;
  vm["menu"].append("about");
  vm["menu"].append("blog");
  vm["menu"].append("licensing");
  Template::ByName("include_test").render(std::cout, vm);
}
```

**output**:

```HTML
<html>
  <head><title>Menu</title><head>
  <body>
    <ul>
	   <li> About </li>
	   <li> Blog </li>
	   <li> Licensing </li>
    </ul>
  </body>
</html>
```

[See all examples](doxygen/examples.html)
