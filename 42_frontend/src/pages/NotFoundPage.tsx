import { Outlet } from "react-router-dom";
// import { Outlet, useLocation } from "react-router-dom";
// import DirectoryPage from "./DirectoryPage";

const NotFoundPage = () => {
  // const location = useLocation();
  // console.log("loc")
  // console.log(location);
  // if (location.pathname.startsWith("/dir/")) {
  //   return DirectoryPage();
  // }
  console.log("not found page");

  return (
    <div>
      <Outlet />
      <div>NotFOund</div>
    </div>
  );
};

export default NotFoundPage;
