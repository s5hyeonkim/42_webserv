import {
  createBrowserRouter,
  Navigate,
  RouterProvider,
  useRouteError,
} from "react-router-dom";
import MainPage from "../pages/MainPage.tsx";
import ChatPage from "../pages/ChatPage.tsx";
import NotFoundPage from "../pages/NotFoundPage.tsx";
import App from "../App.tsx";
import DirectoryPage from "../pages/DirectoryPage.tsx";

const ErrorBoundary = () => {
  const error = useRouteError();
  console.log(error);
  return <div> 해당 폴더 경로는 존재하지 않습니다. </div>;
};

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
            errorElement: <ErrorBoundary />,
          },
          {
            path: "*",
            element: <DirectoryPage />,
            errorElement: <ErrorBoundary />,
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
