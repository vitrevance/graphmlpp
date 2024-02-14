#include <gtest/gtest.h>
#include <graphmlpp.hpp>

TEST(graphmlpp, Simple) {
  nonstd::string_view graphml = R"(
<?xml version='1.0' encoding='utf-8'?>
<graphml xmlns="http://graphml.graphdrawing.org/xmlns" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd">
<key id="d26" for="edge" attr.name="access" attr.type="string"/>
<key id="d25" for="edge" attr.name="service" attr.type="string"/>
<key id="d24" for="edge" attr.name="lanes" attr.type="string"/>
<key id="d23" for="edge" attr.name="tunnel" attr.type="string"/>
<key id="d22" for="edge" attr.name="junction" attr.type="string"/>
<key id="d21" for="edge" attr.name="ref" attr.type="string"/>
<key id="d20" for="edge" attr.name="maxspeed" attr.type="string"/>
<key id="d19" for="edge" attr.name="width" attr.type="string"/>
<key id="d18" for="edge" attr.name="name" attr.type="string"/>
<key id="d17" for="edge" attr.name="bridge" attr.type="string"/>
<key id="d16" for="edge" attr.name="travel_time" attr.type="string"/>
<key id="d15" for="edge" attr.name="speed_kph" attr.type="string"/>
<key id="d14" for="edge" attr.name="geometry" attr.type="string"/>
<key id="d13" for="edge" attr.name="length" attr.type="string"/>
<key id="d12" for="edge" attr.name="reversed" attr.type="string"/>
<key id="d11" for="edge" attr.name="oneway" attr.type="string"/>
<key id="d10" for="edge" attr.name="highway" attr.type="string"/>
<key id="d9" for="edge" attr.name="osmid" attr.type="string"/>
<key id="d8" for="node" attr.name="ref" attr.type="string"/>
<key id="d7" for="node" attr.name="highway" attr.type="string"/>
<key id="d6" for="node" attr.name="street_count" attr.type="string"/>
<key id="d5" for="node" attr.name="x" attr.type="string"/>
<key id="d4" for="node" attr.name="y" attr.type="string"/>
<graph edgedefault="directed">
<data key="d0">2023-07-26 14:25:15</data>
<data key="d1">OSMnx 1.3.1.post0</data>
<data key="d2">epsg:4326</data>
<data key="d3">True</data>
<node id="2591428522">
  <data key="d4">53.4538295</data>
  <data key="d5">141.9744235</data>
  <data key="d6">3</data>
</node>
<node id="2591428524">
  <data key="d4">53.4538961</data>
  <data key="d5">141.9748529</data>
  <data key="d6">3</data>
</node>
<edge source="2515345608" target="2515345606" id="0">
  <data key="d9">87322767</data>
  <data key="d24">1</data>
  <data key="d10">track</data>
  <data key="d11">False</data>
  <data key="d12">True</data>
  <data key="d13">105.03200000000001</data>
  <data key="d14">LINESTRING (142.7621776 46.9311249, 142.7614804 46.9308768, 142.7612719 46.9308831, 142.7610506 46.9309624, 142.7609122 46.9309637)</data>
  <data key="d15">35.0</data>
  <data key="d16">10.8</data>
</edge>
<edge source="2515345608" target="3110930211" id="0">
  <data key="d9">674945017</data>
  <data key="d24">2</data>
  <data key="d10">track</data>
  <data key="d19">4</data>
  <data key="d11">False</data>
  <data key="d12">False</data>
  <data key="d13">478.162</data>
  <data key="d14">LINESTRING (142.7621776 46.9311249, 142.7619916 46.9291963, 142.7620017 46.9272091, 142.7620892 46.9268336)</data>
  <data key="d15">35.0</data>
  <data key="d16">49.2</data>
</edge>
</graph></graphml>
    )";

  gmlpp::Loader loader;
  loader.ReadBuffer(graphml.data(), graphml.size());

  loader.Visit(
      [](auto& node) {
        std::cout << "Node:" << std::endl;
        std::cout << node["id"] << std::endl;
        std::cout << node["x"] << std::endl;
        std::cout << node["y"] << std::endl;
      },
      [](const gmlpp::Loader::ElementView& edge) {
        std::cout << "edge:" << std::endl;
        std::cout << edge["source"] << std::endl;
        std::cout << edge["target"] << std::endl;
        std::cout << edge.ExtractAt<float>("length") << std::endl;
      });
}