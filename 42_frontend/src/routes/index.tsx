import {
  createBrowserRouter,
  Navigate,
  RouterProvider,
} from "react-router-dom";
import MainPage from "../pages/MainPage.tsx";
import ChatPage from "../pages/ChatPage.tsx";
import NotFoundPage from "../pages/NotFoundPage.tsx";
import App from "../App.tsx";
import DirectoryPage from "../pages/DirectoryPage.tsx";

const router = createBrowserRouter([
  {
    element: <App />,
    children: [
      {
        path: "/",
        element: <Navigate to="main" />,
      },
      {
        path: "chatroom",
        element: <ChatPage />,
      },
      {
        path: "main",
        element: <MainPage />,
      },
      {
        path: "/dir",
        children: [
          {
            path: "",
            element: <DirectoryPage />,
          },
          {
            path: "*",
            element: <DirectoryPage />,
          },
        ],
      },
      {
        path: "*",
        element: <NotFoundPage />,
      },
    ],
  },
]);

export default function Router() {
  return <RouterProvider router={router} />;
}
