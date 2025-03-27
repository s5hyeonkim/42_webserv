import { Outlet } from "react-router-dom";

function App() {
  return (
    <div className="app">
      <Outlet />
      {/* <NavBar /> /*/}
      {/* <MainPage /> */}
      {/* <ChatPage /> */}
      {/* <BottomNavBar /> */}
    </div>
  );
}

export default App;
