#include "loop.h"

void CLoop::menu_loop (void) {
  // auto tmp = m_Graphics->getWindowSize();
  // int W = tmp.first, H = tmp.second;
  bool quit = false;
  bool update = true;
  SDL_Event e;

  CButton buttonNew (SDL_Rect({100, 100, 100, 20}), c_Black, c_White, c_White, "New Index");
  CButton buttonSave(SDL_Rect({100, 200, 100, 20}), c_Black, c_White, c_White, "Load Index");
  CButton buttonQuit(SDL_Rect({100, 300, 100, 20}), c_Black, c_White, c_White, "Quit");

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) quit = true;
      else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mx = e.button.x, my = e.button.y;
        if (inside(buttonNew.m_Rectangle, mx, my)) {
          CLoop new_loop(m_Graphics);
          new_loop.new_loop();
          update = true;
        }

        if (inside(buttonSave.m_Rectangle, mx, my)) {
          CLoop save_loop(m_Graphics);
          save_loop.save_loop();
          update = true;
        }

        if (inside(buttonQuit.m_Rectangle, mx, my)) {
          update = true;
          quit = true;
        }
      }
    }

    if (!update) continue;
    
    m_Graphics->clear();
    
    m_Graphics->renderButton(buttonNew);
    m_Graphics->renderButton(buttonSave);
    m_Graphics->renderButton(buttonQuit);

    m_Graphics->render();

    
    update = false;
  }
}

void CLoop::save_loop (void) {
  SDL_StartTextInput();
  bool quit = false;
  bool update = true;
  SDL_Event e;
  
  std::vector<CButton> files;

  int cnt = 100;

  for (const auto& entry : std::filesystem::directory_iterator(SAVES_DIR)) {
    files.emplace_back(SDL_Rect({100, cnt, 400, 20}), c_Black, c_Black, c_White, entry.path());
    cnt += 100;
  }

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) quit = true;
      else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mx = e.button.x, my = e.button.y;

        for (const auto& it: files)
          if (inside(it.m_Rectangle, mx, my)) {

            CLoop rtree_loop(m_Graphics);
            CIndex* index = new CRTree(1, 1, 2, true);
            
            printf("Loading %s.\n", it.m_Text.c_str());
            if (!index->load(it.m_Text))
              printf("Error while loading.");

            rtree_loop.rtree_loop(index,
                                  BASE_RANDOM_NUMBER,
                                  BASE_DELAY,
                                  true,
                                  true,
                                  true
                                );
            delete index;
            update = true;
          }
      }
    }

    if (!update) continue;
    
    m_Graphics->clear();
    
    for (const auto& it: files)
      m_Graphics->renderButton(it);

    m_Graphics->render();

    
    update = false;
  }
  SDL_StopTextInput();
}

void CLoop::new_loop (void) {
  // auto tmp = m_Graphics->getWindowSize();
  // int W = tmp.first, H = tmp.second;
  bool quit = false;
  bool update = true;
  SDL_Event e;
  SDL_StartTextInput();

  int buttonWidth = 200;

  size_t  MAX_DIMENSION_LEN = 1;
  bool    textBoxDimensionActive = false;
  CText   textBoxDimensionText(SDL_Rect({50, 100,  50, 20}), c_White, "Dimension:");
  CButton textBoxDimension (SDL_Rect({250, 100, buttonWidth, 20}), c_Black, c_White, c_White, "2");

  size_t  MAX_MIN_LEN = 2;
  bool    textBoxMinActive = false;
  CText   textBoxMinText(SDL_Rect({50, 150,  50, 20}), c_White, "Min records:");
  CButton textBoxMin(SDL_Rect({250, 150, buttonWidth, 20}), c_Black, c_White, c_White, "5");
  
  size_t  MAX_MAX_LEN = 2;
  bool    textBoxMaxActive = false;
  CText   textBoxMaxText(SDL_Rect({50, 200,  50, 20}), c_White, "Max records:");
  CButton textBoxMax(SDL_Rect({250, 200, buttonWidth, 20}), c_Black, c_White, c_White, "10");

  size_t  MAX_RANDOM_LEN = 7;
  bool    textBoxRandomActive = false;
  CText   textBoxRandomText(SDL_Rect({50, 250,  50, 20}), c_White, "Number of random:");
  CButton textBoxRandom(SDL_Rect({250, 250, buttonWidth, 20}), c_Black, c_White, c_White, "10");

  size_t  MAX_DELAY_LEN = 5;
  bool    textBoxDelayActive = false;
  CText   textBoxDelayText(SDL_Rect({50, 300,  50, 20}), c_White, "Insert delay:");
  CButton textBoxDelay(SDL_Rect({250, 300, buttonWidth, 20}), c_Black, c_White, c_White, "500");

  CText     checkBoxAxesText(SDL_Rect({50, 350,  50, 20}), c_White, "Axes:");
  CCheckBox checkBoxAxes(SDL_Rect({250, 350, 20, 20}), c_Black, c_White, true);

  CText     checkBoxVisualizeText(SDL_Rect({50, 400,  50, 20}), c_White, "Visualize:");
  CCheckBox checkBoxVisualize(SDL_Rect({250, 400, 20, 20}), c_Black, c_White, true);

  CText     checkBoxRtreeText(SDL_Rect({50, 450,  50, 20}), c_White, "RTree:");
  CCheckBox checkBoxRtree(SDL_Rect({250, 450, 20, 20}), c_Black, c_White, true);

  CText     checkBoxQuadraticText(SDL_Rect({50, 500,  50, 20}), c_White, "Quadratic:");
  CCheckBox checkBoxQuadratic(SDL_Rect({250, 500, 20, 20}), c_Black, c_White, true);

  CText     checkBoxPrintText(SDL_Rect({50, 550,  50, 20}), c_White, "Print:");
  CCheckBox checkBoxPrint(SDL_Rect({250, 550, 20, 20}), c_Black, c_White, true);

  CButton buttonContinue(SDL_Rect({250, 650, 80, 20}), c_Black, c_White, c_White, "Continue");

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) quit = true;
      else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mx = e.button.x, my = e.button.y;

        textBoxDimensionActive = false;
        textBoxMinActive = false;
        textBoxMaxActive = false;
        textBoxRandomActive = false;
        textBoxDelayActive = false;

        if (inside(textBoxDimension.m_Rectangle, mx, my)) {
          textBoxDimensionActive = true;
          update = true;
        } 
        else if (inside(textBoxMin.m_Rectangle, mx, my)){
          textBoxMinActive = true;
          update = true;
        }
        else if (inside(textBoxMax.m_Rectangle, mx, my)){
          textBoxMaxActive = true;
          update = true;
        }
        else if (inside(textBoxRandom.m_Rectangle, mx, my)){
          textBoxRandomActive = true;
          update = true;
        }
        else if (inside(textBoxDelay.m_Rectangle, mx, my)){
          textBoxDelayActive = true;
          update = true;
        }
        else if (inside(checkBoxAxes.m_Rectangle, mx, my)){
          checkBoxAxes.m_Status = checkBoxAxes.m_Status ? false : true;
          update = true;
        }
        else if (inside(checkBoxVisualize.m_Rectangle, mx, my)){
          checkBoxVisualize.m_Status = checkBoxVisualize.m_Status ? false : true;
          update = true;
        }
        else if (inside(checkBoxRtree.m_Rectangle, mx, my)){
          checkBoxRtree.m_Status = checkBoxRtree.m_Status ? false : true;
          update = true;
        }
        else if (inside(checkBoxQuadratic.m_Rectangle, mx, my)){
          checkBoxQuadratic.m_Status = checkBoxQuadratic.m_Status ? false : true;
          update = true;
        }
        else if (inside(checkBoxPrint.m_Rectangle, mx, my)){
          checkBoxPrint.m_Status = checkBoxPrint.m_Status ? false : true;
          update = true;
        }

        if (inside(buttonContinue.m_Rectangle, mx, my)) {
          if (textBoxDimension.m_Text.empty() || textBoxMin.m_Text.empty() || textBoxMax.m_Text.empty() || textBoxRandom.m_Text.empty() || textBoxDelay.m_Text.empty()) {
            printf("Wrong input size.\n");
            continue;
          }

          int dimension = std::stoi(textBoxDimension.m_Text);
          int minRecords = std::stoi(textBoxMin.m_Text);
          int maxRecords = std::stoi(textBoxMax.m_Text);
          int randomNumber = std::stoi(textBoxRandom.m_Text);
          int delay = std::stoi(textBoxDelay.m_Text);

          if (dimension < 2) {printf("Dimension: %d. Must be > 1.\n", dimension); continue;}
          if (minRecords < 1) {printf("Min records: %d. Must be > 0.\n", minRecords); continue;}
          if (maxRecords < 1 || maxRecords <= minRecords) {printf("Max records: %d. Must be > 0 and < %d.\n", maxRecords, minRecords); continue;}

          CLoop rtree_loop(m_Graphics);
          CIndex* index = nullptr;
          if (checkBoxRtree.m_Status)
            if (checkBoxQuadratic.m_Status)
              index = new CRTree(dimension, minRecords, maxRecords, true);
            else
              index = new CRTree(dimension, minRecords, maxRecords, false);
          else 
            index = new CBruteForce(dimension);

          rtree_loop.rtree_loop(index,
                                randomNumber,
                                delay,
                                checkBoxAxes.m_Status,
                                checkBoxVisualize.m_Status,
                                checkBoxPrint.m_Status
                              );
          delete index;
          update = true;
        }
      }
      else if (textBoxDimensionActive) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && !textBoxDimension.m_Text.empty()) {
          textBoxDimension.m_Text.pop_back();
          update = true;
        }

        if (e.type == SDL_TEXTINPUT) {
          if (textBoxDimension.m_Text.size() < MAX_DIMENSION_LEN && std::isdigit(e.text.text[0]))
            textBoxDimension.m_Text += e.text.text;
          update = true;
        }
      }
      else if (textBoxMinActive) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && !textBoxMin.m_Text.empty()) {
          textBoxMin.m_Text.pop_back();
          update = true;
        }

        if (e.type == SDL_TEXTINPUT) {
          if (textBoxMin.m_Text.size() < MAX_MIN_LEN && std::isdigit(e.text.text[0]))
            textBoxMin.m_Text += e.text.text;
          update = true;
        }
      }
      else if (textBoxMaxActive) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && !textBoxMax.m_Text.empty()) {
          textBoxMax.m_Text.pop_back();
          update = true;
        }

        if (e.type == SDL_TEXTINPUT) {
          if (textBoxMax.m_Text.size() < MAX_MAX_LEN && std::isdigit(e.text.text[0]))
            textBoxMax.m_Text += e.text.text;
          update = true;
        }
      }
      else if (textBoxRandomActive) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && !textBoxRandom.m_Text.empty()) {
          textBoxRandom.m_Text.pop_back();
          update = true;
        }

        if (e.type == SDL_TEXTINPUT) {
          if (textBoxRandom.m_Text.size() < MAX_RANDOM_LEN && std::isdigit(e.text.text[0]))
            textBoxRandom.m_Text += e.text.text;
          update = true;
        }
      }
      else if (textBoxDelayActive) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && !textBoxDelay.m_Text.empty()) {
          textBoxDelay.m_Text.pop_back();
          update = true;
        }

        if (e.type == SDL_TEXTINPUT) {
          if (textBoxDelay.m_Text.size() < MAX_DELAY_LEN && std::isdigit(e.text.text[0]))
            textBoxDelay.m_Text += e.text.text;
          update = true;
        }
      }
    }

    if (!update) continue;
    
    m_Graphics->clear();
    
    m_Graphics->renderText(textBoxDimensionText);
    m_Graphics->renderText(textBoxMinText);
    m_Graphics->renderText(textBoxMaxText);
    m_Graphics->renderText(textBoxRandomText);
    m_Graphics->renderText(textBoxDelayText);

    m_Graphics->renderButton(textBoxDimension);
    m_Graphics->renderButton(textBoxMin);
    m_Graphics->renderButton(textBoxMax);
    m_Graphics->renderButton(textBoxRandom);
    m_Graphics->renderButton(textBoxDelay);

    m_Graphics->renderText(checkBoxAxesText);
    m_Graphics->renderCheckBox(checkBoxAxes);
    m_Graphics->renderText(checkBoxVisualizeText);
    m_Graphics->renderCheckBox(checkBoxVisualize);
    m_Graphics->renderText(checkBoxRtreeText);
    m_Graphics->renderCheckBox(checkBoxRtree);
    m_Graphics->renderText(checkBoxPrintText);
    m_Graphics->renderCheckBox(checkBoxPrint);
    m_Graphics->renderText(checkBoxQuadraticText);
    m_Graphics->renderCheckBox(checkBoxQuadratic);

    m_Graphics->renderButton(buttonContinue);

    m_Graphics->render();

    update = false;
  }
  SDL_StopTextInput();
}

// void CLoop::rtree_loop (int dimension, int minRecords, int maxRecords, int randomNumber, int delay, bool axes, bool visualize, bool useRtree, bool print) {
void CLoop::rtree_loop (CIndex* index, int randomNumber, int delay, bool axes, bool visualize, bool print) {

  auto tmp = m_Graphics->getWindowSize();
  int W = tmp.first, H = tmp.second;

  std::random_device                 rand_dev{};
  std::mt19937                       gen(rand_dev());
  std::uniform_int_distribution<int> x_uniform(-W / 2 + 20, W / 2 - 20);
  std::uniform_int_distribution<int> y_uniform(-((H - INTERFACE_Y) / 2) + 20, ((H - INTERFACE_Y) / 2) - 20);

  bool quit = false;
  bool update = true;
  bool toDelay = false;
  bool query = false;
  bool knn = false;

  std::vector<CRecord*> queryResult;

  CPoint queryBottomLeft;
  CPoint queryTopRight;
  CPoint queryKNN;
  SDL_Event e;
  
  std::string baseCoordinates("(");
  for (size_t i = 0; i < index->dimension(); ++i) baseCoordinates += i == index->dimension() - 1 ? "0.0" : "0.0, ";
  baseCoordinates += ")";
 
  std::string minus100("(");
  for (size_t i = 0; i < index->dimension(); ++i) minus100 += i == index->dimension() - 1 ? "-100.0" : "-100.0, ";
  minus100 += ")";

  std::string plus100("(");
  for (size_t i = 0; i < index->dimension(); ++i) plus100 += i == index->dimension() - 1 ? "100.0" : "100.0, ";
  plus100 += ")";

  bool    textBoxInsertActive = false;
  CButton textBoxInsert (SDL_Rect({50, 50, 300, 20}), c_Black, c_White, c_White, minus100);
  CButton buttonInsert  (SDL_Rect({400, 50, 50, 20}), c_Black, c_White, c_White, "Insert");

  bool    textBoxKNNActive = false;
  CButton textBoxKNN    (SDL_Rect({480, 50, 50, 20}), c_Black, c_White, c_White, "3");
  CButton buttonKNN     (SDL_Rect({550, 50, 50, 20}), c_Black, c_White, c_White, "KNN");

  bool    textBoxRangeActive = false;
  CButton textBoxRange  (SDL_Rect({50, 100, 300, 20}), c_Black, c_White, c_White, plus100);
  CButton buttonRange   (SDL_Rect({400, 100, 50, 20}), c_Black, c_White, c_White, "Range");

  CButton buttonSave    (SDL_Rect({400, 150, 50, 20}), c_Black, c_White, c_White, "Save");

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) quit = true;
      else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mx = e.button.x, my = e.button.y;

        textBoxInsertActive = false;
        textBoxRangeActive = false;
        textBoxKNNActive = false;

        if (inside(textBoxInsert.m_Rectangle, mx, my)) {
          textBoxInsertActive = true;
          update = true;
        }

        if (inside(textBoxRange.m_Rectangle, mx, my)) {
          textBoxRangeActive = true;
          update = true;
        }
        if (inside(textBoxKNN.m_Rectangle, mx, my)) {
          textBoxKNNActive = true;
          update = true;
        }

        if (inside(buttonInsert.m_Rectangle, mx, my)) {
          update = true;
          CPoint newPoint = parseCoordinates(index->dimension(), textBoxInsert.m_Text);
          if (newPoint.m_Coordinates.empty()) {
            printf("Wrong input format. Try %s.\n", baseCoordinates.c_str());
            textBoxInsert.m_Text = baseCoordinates;
            continue;
          }

          if (print) {
            printf("Inserting (");
            for (size_t i = 0; i < newPoint.m_Coordinates.size(); ++i)   
              printf(i == newPoint.m_Coordinates.size() - 1 ? "%lf" : "%lf,", newPoint.m_Coordinates[i]);
            printf("), with ID = %zu.\n", index->size());
          }
          
          index->insert(new CRecord(index->size(), newPoint));
        }
        if (inside(buttonRange.m_Rectangle, mx, my)) {
          update = true;
          queryBottomLeft = parseCoordinates(index->dimension(), textBoxInsert.m_Text);
          queryTopRight   = parseCoordinates(index->dimension(), textBoxRange.m_Text);

          if (queryBottomLeft.m_Coordinates.empty()) {
            printf("Wrong input format. Try %s.\n", baseCoordinates.c_str());
            textBoxInsert.m_Text = baseCoordinates;
            continue;
          }
          if (queryTopRight.m_Coordinates.empty()) {
            printf("Wrong input format. Try %s.\n", baseCoordinates.c_str());
            textBoxRange.m_Text = baseCoordinates;
            continue;
          }
          if (!(queryBottomLeft < queryTopRight)) {
            printf("First point must be < than second. \n");
            textBoxInsert.m_Text = baseCoordinates;
            textBoxRange.m_Text = baseCoordinates;
            continue;
          }

          queryResult = index->find_in_range(CBoundaries(queryBottomLeft, queryTopRight));

          if (print) {
            printf("Querying in rectangle: from (");
            for (size_t i = 0; i < queryBottomLeft.m_Coordinates.size(); ++i)
              printf(i == queryBottomLeft.m_Coordinates.size() - 1 ? "%lf" : "%lf,", queryBottomLeft.m_Coordinates[i]);
            printf(") to (");
            for (size_t i = 0; i < queryTopRight.m_Coordinates.size(); ++i)
              printf(i == queryTopRight.m_Coordinates.size() - 1 ? "%lf" : "%lf,", queryTopRight.m_Coordinates[i]);
            printf(").\n");
  
            printf("Found IDs: (");
            for (size_t i = 0; i < queryResult.size(); ++i)
              printf(i == queryResult.size() - 1 ? "%zu" : "%zu,", queryResult[i]->m_Id);
            printf(").\n");
          }
          query = true;
        }
        if (inside(buttonKNN.m_Rectangle, mx, my)) {
          update = true;
          queryKNN = parseCoordinates(index->dimension(), textBoxInsert.m_Text);
          size_t k = std::stoull(textBoxKNN.m_Text);

          if (queryKNN.m_Coordinates.empty()) {
            printf("Wrong input format. Try %s.\n", baseCoordinates.c_str());
            textBoxInsert.m_Text = baseCoordinates;
            continue;
          }

          queryResult = index->knn(queryKNN, k);

          if (print) {
            printf("Querying KNN (%zu) near: (", k);
            for (size_t i = 0; i < queryKNN.m_Coordinates.size(); ++i)
              printf(i == queryKNN.m_Coordinates.size() - 1 ? "%lf" : "%lf,", queryKNN.m_Coordinates[i]);
            printf(").\n");
  
            printf("Found IDs: (");
            for (size_t i = 0; i < queryResult.size(); ++i)
              printf(i == queryResult.size() - 1 ? "%zu" : "%zu,", queryResult[i]->m_Id);
            printf(").\n");
          }
          knn = true;
        }
        if (inside(buttonSave.m_Rectangle, mx, my)) {
          std::string name = SAVES_DIR + getCurrentTimeString();
          printf("Saving %s.\n", (name).c_str());
          if (!index->save(name)) {
            printf("Error while saving.");
            if (std::filesystem::exists(name))
              std::filesystem::remove(name);   
          }
          update = true;
        }
      }
      else if (textBoxInsertActive) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && !textBoxInsert.m_Text.empty()) {
          textBoxInsert.m_Text.pop_back();
          update = true;
        }

        if (e.type == SDL_TEXTINPUT) {
          if (textBoxInsert.m_Text.size() < 30)
            textBoxInsert.m_Text += e.text.text;
          update = true;
        }
      }
      else if (textBoxRangeActive) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && !textBoxRange.m_Text.empty()) {
          textBoxRange.m_Text.pop_back();
          update = true;
        }

        if (e.type == SDL_TEXTINPUT) {
          if (textBoxRange.m_Text.size() < 30)
            textBoxRange.m_Text += e.text.text;
          update = true;
        }
      }
      else if (textBoxKNNActive) {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && !textBoxKNN.m_Text.empty()) {
          textBoxKNN.m_Text.pop_back();
          update = true;
        }

        if (e.type == SDL_TEXTINPUT) {
          if (textBoxKNN.m_Text.size() < 3 && std::isdigit(e.text.text[0]))
          textBoxKNN.m_Text += e.text.text;
          update = true;
        }
      }
    }

    if (randomNumber > 0) {
      std::vector<double> il(index->dimension());
      for (size_t i = 0; i < index->dimension(); ++i)
        il[i] = i == 0 ? static_cast<double>(x_uniform(gen)) : static_cast<double>(y_uniform(gen));

      if (print) {
        printf("Inserting (");
        for (size_t i = 0; i < il.size(); ++i)   
        printf(i == il.size() - 1 ? "%lf" : "%lf,", il[i]);
        printf("), with ID = %zu.\n", index->size());
      }

      index->insert(new CRecord(index->size(), il));
        
      update = true;

      --randomNumber;
      if (toDelay) SDL_Delay(delay);
    }

  // if (print) {
  //   printf("Executing range query: from (");
  //   for (size_t i = 0; i < m_Dimension; ++i) printf(i == m_Dimension - 1 ? "%lf" : "%lf,", boundaries.m_BottomLeft.m_Coordinates[i]);
  //   printf("), to (");
  //   for (size_t i = 0; i < m_Dimension; ++i) printf(i == m_Dimension - 1 ? "%lf" : "%lf,", boundaries.m_TopRight.m_Coordinates[i]);
  //   printf(").\n");
  // }
      
  
      // if (print) printf("Completed!\n");

    if (!update) continue;
    
    m_Graphics->clear();
    
    // VISUALIZATION
    if (visualize) {
      m_Graphics->renderRectangle(SDL_Rect({0, INTERFACE_Y, W, H - INTERFACE_Y}), c_Gray);
      m_Graphics->renderLine(0, INTERFACE_Y, W, INTERFACE_Y, c_White);
      
      if (axes) {
        m_Graphics->renderLine(0, INTERFACE_Y + (H - INTERFACE_Y) / 2, W, INTERFACE_Y + (H - INTERFACE_Y) / 2, c_White);
        m_Graphics->renderLine(W / 2, INTERFACE_Y, W / 2, H, c_White);
      }

      index->render(m_Graphics, c_Green, c_Blue, INTERFACE_Y);

      if (query) {
        for (size_t i = 0; i < queryResult.size(); ++i)
          m_Graphics->renderCircle(queryResult[i]->m_Position.m_Coordinates[0] + W / 2, H - (queryResult[i]->m_Position.m_Coordinates[1] + (H - INTERFACE_Y) / 2), 5, c_Yellow);

        m_Graphics->renderLine(W / 2 + static_cast<int>(queryBottomLeft.m_Coordinates[0]), INTERFACE_Y + (H - INTERFACE_Y) / 2 - static_cast<int>(queryBottomLeft.m_Coordinates[1]), W / 2 + static_cast<int>(queryTopRight.m_Coordinates[0]),   INTERFACE_Y + (H - INTERFACE_Y) / 2 - static_cast<int>(queryBottomLeft.m_Coordinates[1]), c_Yellow);
        m_Graphics->renderLine(W / 2 + static_cast<int>(queryBottomLeft.m_Coordinates[0]), INTERFACE_Y + (H - INTERFACE_Y) / 2 - static_cast<int>(queryBottomLeft.m_Coordinates[1]), W / 2 + static_cast<int>(queryBottomLeft.m_Coordinates[0]), INTERFACE_Y + (H - INTERFACE_Y) / 2 - static_cast<int>(queryTopRight.m_Coordinates[1]),   c_Yellow);
        m_Graphics->renderLine(W / 2 + static_cast<int>(queryTopRight.m_Coordinates[0]),   INTERFACE_Y + (H - INTERFACE_Y) / 2 - static_cast<int>(queryTopRight.m_Coordinates[1]),   W / 2 + static_cast<int>(queryTopRight.m_Coordinates[0]),   INTERFACE_Y + (H - INTERFACE_Y) / 2 - static_cast<int>(queryBottomLeft.m_Coordinates[1]), c_Yellow);
        m_Graphics->renderLine(W / 2 + static_cast<int>(queryTopRight.m_Coordinates[0]),   INTERFACE_Y + (H - INTERFACE_Y) / 2 - static_cast<int>(queryTopRight.m_Coordinates[1]),   W / 2 + static_cast<int>(queryBottomLeft.m_Coordinates[0]), INTERFACE_Y + (H - INTERFACE_Y) / 2 - static_cast<int>(queryTopRight.m_Coordinates[1]),   c_Yellow);
        query = false;
      }

      if (knn) {
        for (size_t i = 0; i < queryResult.size(); ++i)
          m_Graphics->renderCircle(queryResult[i]->m_Position.m_Coordinates[0] + W / 2, H - (queryResult[i]->m_Position.m_Coordinates[1] + (H - INTERFACE_Y) / 2), 5, c_Yellow);      
        m_Graphics->renderCircle(queryKNN.m_Coordinates[0] + W / 2, H - (queryKNN.m_Coordinates[1] + (H - INTERFACE_Y) / 2), 5, c_Red);
  
        knn = false;
      }
    }

    // INTERFACE
    m_Graphics->renderRectangle(SDL_Rect({0, 0, W, INTERFACE_Y}), c_Black);
    m_Graphics->renderButton(textBoxInsert);
    m_Graphics->renderButton(buttonInsert);
    
    m_Graphics->renderButton(textBoxKNN);
    m_Graphics->renderButton(buttonKNN);
    
    m_Graphics->renderButton(textBoxRange);
    m_Graphics->renderButton(buttonRange);
    
    m_Graphics->renderButton(buttonSave);

    m_Graphics->render();

    update = false;
    if (!toDelay) toDelay = true;
  }
}