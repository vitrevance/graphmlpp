#pragma once

#include <pugixml.hpp>
#include <nonstd/string_view.hpp>
#include <stdexcept>
#include <map>

namespace gmlpp {

struct Loader {
 private:
  using KeyMap = std::map<nonstd::string_view, nonstd::string_view>;

 public:
  struct ElementView {
   public:
    ElementView(const ElementView&) = delete;
    ElementView(ElementView&&) = delete;

    nonstd::string_view operator[](nonstd::string_view key) const {
      return Extract<nonstd::string_view>(key);
    }

    template <typename T>
    T Extract(nonstd::string_view key) const = delete;

    template <>
    int Extract<int>(nonstd::string_view key) const {
      return std::atoi(GetAttribute(ConvertKey(key)).data());
    }

    template <>
    float Extract<float>(nonstd::string_view key) const {
      return std::atof(GetAttribute(ConvertKey(key)).data());
    }

    template <>
    int64_t Extract<int64_t>(nonstd::string_view key) const {
      return std::atoll(GetAttribute(ConvertKey(key)).data());
    }

    template <>
    const char* Extract<const char*>(nonstd::string_view key) const {
      return GetAttribute(ConvertKey(key)).data();
    }

    template <>
    nonstd::string_view Extract<nonstd::string_view>(
        nonstd::string_view key) const {
      return GetAttribute(ConvertKey(key));
    }

    bool HasAttribute(nonstd::string_view key) const {
      key = ConvertKey(key);
      return !node_.attribute(key.data()).empty()
             || !node_.find_child_by_attribute("key", key.data()).empty();
    }

    template <typename T>
    T ExtractAt(nonstd::string_view key) const {
      if (!HasAttribute(key)) {
        throw std::runtime_error("Invalid key: " + std::string(key));
      }
      return Extract<T>(key);
    }

    friend Loader;

   private:
    ElementView(pugi::xml_node& node, KeyMap& keys)
        : node_(node),
          keys_(keys) {
    }

    nonstd::string_view ConvertKey(nonstd::string_view key) const {
      auto iter = keys_.find(key);
      if (iter != keys_.end()) {
        return iter->second;
      }
      return key;
    }

    nonstd::string_view GetAttribute(nonstd::string_view key) const {
      if (node_.attribute(key.data()).empty()) {
        return node_.find_child_by_attribute("key", key.data()).child_value();
      }
      return node_.attribute(key.data()).as_string();
    }

    pugi::xml_node& node_;
    KeyMap& keys_;
  };

  void ReadStream(std::istream& stream) {
    pugi::xml_parse_result result = doc_.load(stream);
    if (!result) {
      throw std::runtime_error(result.description());
    }
  }

  void ReadBuffer(const char* buffer, std::size_t size) {
    pugi::xml_parse_result result = doc_.load_buffer(buffer, size);
    if (!result) {
      throw std::runtime_error(result.description());
    }
  }

  void ReadBufferInplace(char* buffer, std::size_t size) {
    pugi::xml_parse_result result = doc_.load_buffer_inplace(buffer, size);
    if (!result) {
      throw std::runtime_error(result.description());
    }
  }

  template <typename OnNode, typename OnEdge>
  void Visit(OnNode&& on_node, OnEdge&& on_edge) {
    pugi::xml_node graphml = doc_.child("graphml");

    KeyMap node_keys;
    KeyMap edge_keys;

    for (auto& key : graphml.select_nodes("key")) {
      if (key.node().attribute("for").as_string()
          == nonstd::string_view("node")) {
        const auto attr_key = key.node().attribute("id").as_string();
        const auto attr_name = key.node().attribute("attr.name").as_string();
        node_keys[attr_name] = attr_key;
      } else if (key.node().attribute("for").as_string()
                 == nonstd::string_view("edge")) {
        const auto attr_key = key.node().attribute("id").as_string();
        const auto attr_name = key.node().attribute("attr.name").as_string();
        edge_keys[attr_name] = attr_key;
      }
    }

    for (pugi::xml_node& node : graphml.child("graph")) {
      if (node.name() == nonstd::string_view("node")) {
        on_node(static_cast<const ElementView&>(ElementView(node, node_keys)));
      } else if (node.name() == nonstd::string_view("edge")) {
        on_edge(static_cast<const ElementView&>(ElementView(node, edge_keys)));
      }
    }
  }

 private:
  pugi::xml_document doc_;
};

}  // namespace gmlpp