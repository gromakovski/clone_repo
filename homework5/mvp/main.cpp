#include <iostream>
#include <memory>
#include <vector>

#include "scene_graph_view.h"
#include "scene_list_view.h"

int main(int argc, char const *argv[]) {
  // ISceneView *view = new SceneGraphView;
  ISceneView *view = new SceneListView;

  view->userInput();

  return 0;
}
